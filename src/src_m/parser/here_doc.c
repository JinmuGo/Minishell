/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:48:12 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/05 16:59:11 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "data_structure.h"
#include "meta_command.h"
#include "expander.h"
#include "signal_controller.h"

void	here_doc(t_list **tk_list, t_deque *dque, t_token *value)
{
	pid_t			pid;
	t_here_doc	*content;
	t_list		*new_unlink;
	char		*file_path;

	file_path = creat_file();
	content = ft_calloc(1, sizeof(t_here_doc));
	new_unlink = ft_calloc(1, sizeof(t_list));
	pid = fork();
	signal_controller(SIG_CHILD, pid);
	if (pid == 0)
		exe_here_doc(tk_list, dque, file_path);
	else
	{
		heredoc_wait(pid);
		signal_controller(SIG_INIT);
		content->fd = open(file_path, O_RDONLY, 0644);
		unlink(file_path);
		content->file = ft_strdup(file_path);
		value->cmd_val.rdr->file = ft_strdup(file_path);
		free(file_path);
		new_unlink->content = content;
		ft_lstadd_back(get_unlink_lst(), new_unlink);
		delete_lst_node(tk_list, ((t_list *)(dque->pop_front(dque)))->content);
	}
}

void	heredoc_wait(pid_t pid)
{
	t_meta	*meta;

	meta = get_meta();
	waitpid(pid, &(meta->exit_status), 0);
	meta->exit_status = WEXITSTATUS(meta->exit_status);
}

void	exe_here_doc(t_list **tk_list, t_deque *dque, char *file_path)
{
	int	fd;

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
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if ((ft_strncmp(line, delimter, ft_strlen(line)) == 0 && \
			ft_strlen(line) == ft_strlen(delimter)))
		{
			free(line);
			break ;
		}
		else if (!line)
		{
			if (write(fd, "\n", 1) == -1)
				perror("infile write error");
		}
		else
		{
			tmp = ft_strjoin(line, "\n");
			if (write(fd, tmp, ft_strlen(line) + 1) == -1)
				perror("infile write error()");
			free(tmp);
		}
		if (line)
			free(line);
	}
}

void	expand_write(int fd, char *delimter)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if ((ft_strncmp(line, delimter, ft_strlen(line)) == 0 && \
			ft_strlen(line) == ft_strlen(delimter)))
		{
			free(line);
			break ;
		}
		else if (!line)
		{
			if (write(fd, "\n", 1) == -1)
				perror("infile write error");
		}
		else
		{
			line = shell_param_expand(line);
			tmp = ft_strjoin(line, "\n"); 
			if (write(fd, tmp, ft_strlen(line) + 1) == -1)
				perror("infile write error()");
			free(tmp);
		}
		if (line)
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

int	validation_heredoc(t_list *token)
{
	const int	err = get_err_num();

	if (ft_strncmp(((t_tokenize *)(token->content))->str, "<<", 3))
		return (0);
	if (token->next == NULL || (err >= ERR_RDR_IN && err <= ERR_RDR_APPEND))
		return (0);
	return (1);
}
