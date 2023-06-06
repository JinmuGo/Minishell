/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:26 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 20:18:39 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

static void	rdr_expander(t_rdr	*rdr)
{
	if (rdr == NULL)
		return ;
	if (rdr->rdr_type != HEREDOC)
	{
		rdr->file = shell_param_expand(rdr->file, NULL);
		if (rdr->file[0] != S_QUOTE || rdr->file[0] != D_QUOTE)
			return ;
		rdr->file = quote_removal(rdr->file);
	}
}

static void	arg_expand(t_simple_cmd *cmd, char *str, int idx)
{
	t_list	*lst;
	t_list	*begin;
	char	*tmp;
	char	*rv;

	lst = split_node(str, ft_strlen(str));
	begin = lst;
	rv = ft_strdup("\0");
	if (lst == NULL)
		return ;
	while (lst)
	{
		tmp = ft_strdup(lst->content);
		lst->content = shell_param_expand(lst->content, lst->next);
		if (ft_strcmp(lst->content, tmp) == 0 || is_in_quote(tmp))
			lst->content = quote_removal(lst->content);
		free(tmp);
		tmp = rv;
		rv = ft_strjoin(tmp, lst->content);
		free(tmp);
		lst = lst->next;
	}
	ft_lstclear(&begin, free);
	free(cmd->args[idx]);
	cmd->args[idx] = rv;
}

static void	cmd_expand(t_simple_cmd *cmd, char *str)
{
	t_list	*lst;
	t_list	*begin;
	char	*tmp;
	char	*rv;

	lst = split_node(str, ft_strlen(str));
	begin = lst;
	rv = ft_strdup("\0");
	if (lst == NULL)
		return ;
	while (lst)
	{
		tmp = ft_strdup(lst->content);
		lst->content = shell_param_expand(lst->content, lst->next);
		free(tmp);
		tmp = rv;
		rv = ft_strjoin(tmp, lst->content);
		free(tmp);
		lst = lst->next;
	}
	ft_lstclear(&begin, free);
	free(cmd->cmd);
	cmd->cmd = rv;
}

static void	cmd_expander(t_simple_cmd *cmd)
{
	const char	*dup_cmd = (const char *)ft_strdup(cmd->cmd);
	const char	**dup_args = (const char **)ft_arrdup((const char **)cmd->args);
	int			i;

	if (cmd == NULL)
		return ;
	cmd_expand(cmd, cmd->cmd);
	cmd_field_split(cmd, dup_cmd);
	if (ft_strcmp(cmd->cmd, dup_cmd) == 0 || is_in_quote(dup_cmd))
		cmd->cmd = quote_removal(cmd->cmd);
	i = 0;
	while (cmd->args[++i])
	{
		if (ft_mini_strchr(cmd->args[i], DOLLAR))
		{
			arg_expand(cmd, cmd->args[i], i);
			arg_field_split(\
				cmd, cmd->args[i], i, ft_arrlen((void **)cmd->args));
		}
		else
			arg_expand(cmd, cmd->args[i], i);
	}
	free((void *)dup_cmd);
	ft_free_all_arr((char **)dup_args);
}

void	expander(t_tree_node *node)
{
	t_token	*token;

	if (node == NULL)
		return ;
	token = (t_token *)(node->value);
	if (token->type == RDR)
		rdr_expander(token->cmd_val.rdr);
	else if (token->type == S_CMD)
		cmd_expander(token->cmd_val.simple_cmd);
	expander(node->left);
	expander(node->right);
}
