/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:48:12 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/27 20:52:06 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "data_structure.h"
#include "meta_command.h"
#include "expander.h"

void	here_doc(t_list **tk_list, t_deque *dque, t_token *value)
{
	t_here_doc	*content;
	t_list		*new_unlink;
	char		*file_path;
	int			pid;
	t_tokenize		*token;

	file_path = creat_file();
	content = ft_calloc(1, sizeof(t_here_doc));
	new_unlink = ft_calloc(1, sizeof(t_list));
	// here_doc signal
	pid = fork();
	if (pid == 0)
		exe_here_doc(tk_list, dque, file_path);
	else
	{
		wait(0);
		// 부모 시그널
		content->fd = open(file_path, O_RDONLY, 0644);
		unlink(file_path);
		content->file = ft_strdup(file_path);
		value->cmd_val.rdr->file = ft_strdup(file_path);
		free(file_path);
		new_unlink->content = content;
		token = ((t_list *)(dque->pop_front(dque)))->content;
		delete_lst_node(tk_list, token);
	}
}

// void	here_doc(t_list **tk_list, t_deque *dque, t_token *value)
// {
// 	t_here_doc	*content;
// 	t_list		*unlink_list;
// 	t_list		*new_list;

// 	unlink_list = get_unlink_lst();
// 	content = exe_here_doc(tk_list, dque, &unlink_list);
// 	value->cmd_val.rdr->file = ft_strdup(content->file);
// 	new_list = ft_calloc(1, sizeof(t_list));
// 	new_list->content = content;
// 	new_list->next = NULL;
// 	ft_lstadd_back(&unlink_list, new_list);
// }

void	exe_here_doc(t_list **tk_list, t_deque *dque, char *file_path)
{
	int			fd;

	fd = open(file_path, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		perror("file open error");
	write_to_file(tk_list, dque, fd);
	close(fd);
	free(file_path);
	exit(EXIT_SUCCESS);
}

char	*creat_file(void)
{
	char	*file_path;
	char	*num_str;
	int		num;

	num = 0;
	num_str = ft_itoa(num);
	file_path = ft_strjoin("/tmp/minishell_tmp", num_str);
	while (file_path)
	{	
		if (access(file_path, F_OK) != 0)
			break ;
		free(num_str);
		free(file_path);
		num_str = ft_itoa(num++);
		file_path = ft_strjoin("/tmp/minishell_tmp", num_str);
	}
	free(num_str);
	return (file_path);
}

void	write_to_file(t_list **tk_list, t_deque *dque, int fd)
{
	t_tokenize	*token;
	char		*delimter;
	char		*new_delimter;

	token = ((t_list *)(dque->pop_front(dque)))->content;
	delimter = token->str;
	new_delimter = NULL;
	if (validation_delimter(delimter, &new_delimter))
		normal_write(fd, new_delimter);
	else
		expand_write(fd, new_delimter);
	free(new_delimter);
	delete_lst_node(tk_list, token);
}

void	normal_write(int fd, char *delimter)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 3);
		line = get_next_line(0);
		if (ft_strncmp(line, delimter, ft_strlen(line) - 1) == 0 && \
			ft_strlen(line) - 1 == ft_strlen(delimter))
		{
			free(line);
			break ;
		}
		if (write(fd, line, ft_strlen(line)) == -1)
			perror("infile write error()");
		free(line);
	}
}

void	expand_write(int fd, char *delimter)
{
	char	*line;
	char	*expand_line;

	while (1)
	{
		write(1, "> ", 3);
		line = get_next_line(0);
		if (ft_strncmp(line, delimter, ft_strlen(line) - 1) == 0 && \
			ft_strlen(line) - 1 == ft_strlen(delimter))
		{
			free(line);
			break ;
		}
		line = shell_param_expand(line);
		if (write(fd, line, ft_strlen(line)) == -1)
			perror("write error");
		free(line);
	}
}

int	check_heredoc_quote(char *str)
{
	int	quote;
	int	idx;

	idx = 0;
	quote = 0;
	while (str && str[idx])
	{
		if (str[idx] == '\'' || str[idx] == '\"')
		{
			quote = 1;
			break ;
		}
		idx++;
	}
	return (quote);
}

int	validation_delimter(char *delimter, char **new_delimter)
{
	int	quote;

	quote = check_heredoc_quote(delimter);
	*new_delimter = edit_delimter(delimter);
	printf("delimter: %s\n", *new_delimter);
	return (quote);
}

char	*edit_delimter(char *delimter)
{
	int		size;

	size = get_new_delimter_size(delimter);
	return (make_new_delimter(delimter, size));
}

int	get_new_delimter_size(char *delimter)
{
	int		size;
	int		idx;
	t_stack	quote;

	idx = 0;
	size = 0;
	stack_init(&quote);
	while(delimter && delimter[idx])
	{
		if (quote.size > 0 && delimter[idx] == *(char *)quote.peek(&quote))
		{
			quote.pop(&quote);
			idx++;	
		}
		else if (quote.size == 0 && (delimter[idx] == '\'' || delimter[idx] == '\"'))
			quote.push(&quote, &delimter[idx++]);
		else
		{
			idx++;
			size++;
		}
	}
	stack_destory(&quote);
	return (size);
}

char	*make_new_delimter(char *delimter, int size)
{
	t_stack	quote;
	int		idx;
	int		new_idx;
	char	*new_delimter;

	stack_init(&quote);
	new_delimter = ft_calloc(1, size + 1);
	idx = 0;
	new_idx = 0;
	while (delimter && delimter[idx])
	{
		if (quote.size > 0 && delimter[idx] == *(char *)quote.peek(&quote))
		{
			quote.pop(&quote);
			idx++;
		}
		else if (quote.size == 0 && (delimter[idx] == '\'' || delimter[idx] == '\"'))
			quote.push(&quote, &delimter[idx++]);
		else
			new_delimter[new_idx++] = delimter[idx++];
	}
	return (new_delimter);
}
