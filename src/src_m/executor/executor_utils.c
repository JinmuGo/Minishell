/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:03:30 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 11:37:26 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"
#include "executor.h"

t_token_type	check_token_type(t_tree_node *node)
{
	if (node == NULL)
		return (NONE);
	return (((t_token *)(node->value))->type);
}

t_bool	is_built_in(t_tree_node *root)
{
	t_simple_cmd_type	s_type;

	if (root == NULL || root->right == NULL || root->right->right == NULL)
		return (FT_FALSE);
	s_type = is_built_in_cmd(\
	(((t_token *)(root->right->right->value))->cmd_val.simple_cmd)->cmd);
	if (s_type != FT_EXTERNAL)
		return (FT_TRUE);
	else
		return (FT_FALSE);
}

t_bool	is_single(t_tree_node *root)
{
	const t_token_type	t_type = ((t_token *)(root->right->value))->type;

	if (t_type != PIPE)
		return (FT_TRUE);
	else
		return (FT_FALSE);
}

void	shlvl_control(char *proc_name)
{
	int	val;

	if (ft_strcmp(proc_name, "./minishell"))
		return ;
	val = ft_atoi(get_envp_elem("SHLVL")->val);
	set_envp_elem("SHLVL", ft_itoa(val - 1));
}
