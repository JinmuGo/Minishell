/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:47:10 by jgo               #+#    #+#             */
/*   Updated: 2023/03/16 20:41:28 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "envp_command.h"
#include "meta_command.h"
#include "data_structure.h"

void	close_unlink_list(void *content)
{
	t_here_doc	*heredoc;

	if (content)
	{
		heredoc = content;
		free(heredoc->file);
		close(heredoc->fd);
		free(heredoc);
		heredoc = NULL;
	}
}

char	*redef_cur_dir(char *prev_dir)
{
	char	*buffer;
	char	*dst;

	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
		return (prev_dir);
	if (prev_dir)
		free(prev_dir);
	dst = ft_strdup(buffer);
	free(buffer);
	return (dst);
}

void	free_parser_node(t_tree_node *node)
{
	t_token	*token;

	token = node->value;
	if (token->type == RDR)
	{
		free(token->cmd_val.rdr->file);
		free(token->cmd_val.rdr);
	}
	else if (token->type == S_CMD)
	{
		free(token->cmd_val.simple_cmd->cmd);
		ft_free_all_arr(token->cmd_val.simple_cmd->args);
		free(token->cmd_val.simple_cmd);
	}
	else if (token->type == PIPE)
		free(token->cmd_val.pipe);
}

void	clear_asset(char *line, t_tree *tree, t_meta *meta)
{
	free(line);
	pre_order_traversal(tree->root, free_parser_node);
	destroy(tree);
	tree->root = NULL;
	ft_lstclear(get_unlink_lst(), close_unlink_list);
	meta->unlink_lst = ft_calloc(1, sizeof(t_list));
	meta->err = ERR_NOTHING;
}
