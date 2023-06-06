/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:51:55 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 15:21:32 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include "meta_command.h"
#include "parser.h"

void	rdr_heredoc(t_rdr *rdr)
{
	t_list		**unlink_lst;
	t_list		*lst;
	t_here_doc	*here_doc;

	(void)rdr;
	unlink_lst = get_unlink_lst();
	lst = *unlink_lst;
	here_doc = ((t_here_doc *)(lst->content));
	prt_sc_err(dup2(here_doc->fd, STDIN_FILENO));
	edit_unlink_list();
	close(here_doc->fd);
}

void	rdr_restore(t_executor *execute)
{
	prt_sc_err(dup2(execute->in_fd, STDIN_FILENO));
	prt_sc_err(dup2(execute->out_fd, STDOUT_FILENO));
	close(execute->in_fd);
	close(execute->out_fd);
}

int	open_file(t_rdr *rdr)
{
	if (rdr->rdr_type == IN)
		return (open(rdr->file, O_RDONLY, 0644));
	else if (rdr->rdr_type == OUT)
		return (open(rdr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (rdr->rdr_type == APPEND)
		return (open(rdr->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (0);
}

void	rdr_executor(t_tree_node *node, t_executor *execute)
{
	t_rdr	*rdr;
	int		fd;

	if (node == NULL)
		return ;
	rdr = ((t_token *)(node->value))->cmd_val.rdr;
	fd = open_file(rdr);
	if (fd == -1)
	{
		prt_built_in_err(rdr->file, NULL, ERR_NO_SUCH_FILE, EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	if (rdr->rdr_type == IN)
		prt_sc_err(dup2(fd, STDIN_FILENO));
	else if (rdr->rdr_type == HEREDOC)
		rdr_heredoc(rdr);
	else
		prt_sc_err(dup2(fd, STDOUT_FILENO));
	if (rdr->rdr_type != HEREDOC)
		close(fd);
	rdr_executor(node->left, execute);
}
