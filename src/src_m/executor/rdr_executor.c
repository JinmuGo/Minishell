/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:51:55 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 11:13:28 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"

void    rdr_heredoc(t_rdr *rdr)
{
	// here_doc은 open 할 필요없다. (특별하게 처리)

	// unlink_lst를 이용해 unlink할 것.
}

void	rdr_restore(t_executor *execute)
{
	prt_sc_err(dup2(execute->in_fd, STDIN_FILENO));
	prt_sc_err(dup2(execute->out_fd, STDOUT_FILENO));
	close(execute->in_fd);
	close(execute->out_fd);
}

int		open_file(t_rdr *rdr)
{
	int		fd;

	if (rdr->rdr_type == IN)
		fd = open(rdr->file, O_RDONLY, 0644);
	else if (rdr->rdr_type == OUT)
		fd = open(rdr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rdr->rdr_type == APPEND)
		fd = open(rdr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		rdr_heredoc(rdr);
	return (fd);
}

void    rdr_executor(t_tree_node *node, t_executor *execute)
{
	t_rdr	*rdr;
	int		fd;

	if (node == NULL)
		return ;
	rdr = ((t_token *)(node->value))->cmd_val.rdr;
	fd = open_file(rdr);
	if (rdr->rdr_type == IN || rdr->rdr_type == HEREDOC)
		 prt_sc_err(dup2(fd, STDIN_FILENO));
	else
		 prt_sc_err(dup2(fd, STDOUT_FILENO));
	close(fd);
	rdr_executor(node->left, execute);
}
