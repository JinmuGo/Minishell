/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:48:12 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/17 16:55:27 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "meta_command.h"
#include "signal_controller.h"
#include "error.h"

void	here_doc(t_list **tk_list, t_deque *dque, t_token *value)
{
	pid_t		pid;
	char		*file_path;

	file_path = creat_file();
	pid = fork();
	signal_controller(SIG_HERE, pid);
	if (pid == 0)
		exe_here_doc(tk_list, dque, file_path);
	else
	{
		heredoc_wait(pid);
		set_heredoc(file_path, value);
		delete_lst_node(tk_list, ((t_list *)(dque->pop_front(dque)))->content);
	}
}

void	set_heredoc(char *file_path, t_token *value)
{
	t_here_doc	*content;
	t_list		*new_unlink;

	content = ft_calloc(1, sizeof(t_here_doc));
	new_unlink = ft_calloc(1, sizeof(t_list));
	content->fd = open(file_path, O_RDONLY, 0644);
	prt_sc_err(content->fd);
	unlink(file_path);
	content->file = ft_strdup(file_path);
	value->cmd_val.rdr->file = ft_strdup(file_path);
	free(file_path);
	new_unlink->content = content;
	ft_lstadd_back(get_unlink_lst(), new_unlink);
}

void	heredoc_wait(pid_t pid)
{
	t_meta	*meta;

	meta = get_meta();
	waitpid(pid, &(meta->exit_status), 0);
	signal_controller(SIG_INIT, 0);
	meta->exit_status = WEXITSTATUS(meta->exit_status);
}

void	exe_here_doc(t_list **tk_list, t_deque *dque, char *file_path)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT, 0644);
	prt_sc_err(fd);
	write_to_file(tk_list, dque, fd);
	close(fd);
	free(file_path);
	exit(EXIT_SUCCESS);
}

t_bool	validation_heredoc(t_list *token, t_deque *dque)
{
	const int	err = get_err_num();

	if (token->next != dque->nodes[(dque->front + 1) % dque->capacity] \
		&& err != ERR_NL)
	{
		set_err_num(ERR_PIPE);
		return (FT_FALSE);
	}
	if (ft_strncmp(((t_tokenize *)(token->content))->str, "<<", 3))
		return (FT_FALSE);
	if (token->next == NULL || (err >= ERR_RDR_IN && err <= ERR_RDR_APPEND))
		return (FT_FALSE);
	return (FT_TRUE);
}
