/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:25:35 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 11:46:04 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "built_in.h"
#include "executor.h"
#include "meta_command.h"

int	s_built_in_exec(t_tree_node *root, t_executor *execute)
{
	t_simple_cmd_type	type;
	t_simple_cmd		*simple_cmd;

	simple_cmd = ((t_token *)(root->right->right->value))->cmd_val.simple_cmd;
	if (simple_cmd == NULL)
		return (EXIT_FAILURE);
	rdr_executor(root->right->left, execute);
	type = is_built_in_cmd(simple_cmd->cmd);
	return (built_in(simple_cmd, type));
}

int	built_in(t_simple_cmd *simple_cmd, t_simple_cmd_type type)
{
	const t_built_in_func	fp[7] = {\
		ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
	const int				exit_status = fp[type](simple_cmd);

	set_exit_status(exit_status);
	return (exit_status);
}
