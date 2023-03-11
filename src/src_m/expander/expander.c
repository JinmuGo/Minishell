/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:26 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 11:40:28 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

void	rdr_expander(t_rdr	*rdr)
{
	if (rdr == NULL)
		return ;
	if (rdr->rdr_type != HEREDOC)
	{
		rdr->file = shell_param_expand(rdr->file);
		if (rdr->file[0] != S_QUOTE || rdr->file[0] != D_QUOTE)
			return ;
		rdr->file = quote_removal(rdr->file);
	}
}

void	arg_expand(t_simple_cmd *cmd, char *str, int idx)
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
		lst->content = shell_param_expand(lst->content);
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

void	arg_field_split_proc(\
	t_simple_cmd *cmd, char **splited_cmd, const int origin_len)
{
	const int	len = ft_arrlen((void *)splited_cmd);
	char		**args;
	int			i;
	int			idx;

	if (*splited_cmd == NULL)
		return ;
	free(cmd->cmd);
	cmd->cmd = ft_strdup(splited_cmd[0]);
	args = ft_malloc(sizeof(char *) * (len + origin_len));
	i = -1;
	idx = 0;
	while (++i < len)
		args[idx++] = ft_strdup(splited_cmd[i]);
	i = 0;
	while (cmd->args[++i])
		args[idx++] = ft_strdup(cmd->args[i]);
	ft_free_all_arr(cmd->args);
	args[idx] = NULL;
	cmd->args = args;
}

void	cmd_expander(t_simple_cmd *cmd)
{
	const char	*dup_cmd = (const char *)ft_strdup(cmd->cmd);
	const char	**dup_args = (const char **)ft_arrdup((const char **)cmd->args);
	t_bool		expanded;
	int			i;

	if (cmd == NULL)
		return ;
	cmd->cmd = shell_param_expand(cmd->cmd);
	if (ft_strcmp(cmd->cmd, dup_cmd) == 0 || is_in_quote(dup_cmd))
		cmd->cmd = quote_removal(cmd->cmd);
	cmd_field_split(cmd);
	i = 0;
	while (cmd->args[++i])
	{
		if (ft_strchr(cmd->args[i], DOLLAR))
		{
			arg_expand(cmd, cmd->args[i], i);
			arg_field_split(\
				cmd, cmd->args[i], i, ft_arrlen((void **)cmd->args[i]));
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
