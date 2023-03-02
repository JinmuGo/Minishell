/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:25:35 by jgo               #+#    #+#             */
/*   Updated: 2023/03/02 15:33:08 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "built_in.h"
#include "executor.h"

// FT_ECHO = 0,
// FT_CD = 1,
// FT_PWD = 2,
// FT_EXPORT = 3,
// FT_UNSET = 4,
// FT_ENV = 5,
// FT_EXIT = 6,
// FT_EXTERNAL = 7

void    s_built_in_exec(t_tree_node *root, t_executor *execute)
{
    t_bool s_built_in;
    t_simple_cmd_type type;
    t_simple_cmd *simple_cmd = ((t_token *)(root->right->right->value))->cmd_val.simple_cmd;

    if (simple_cmd == NULL)
        return ;
    rdr_executor(root->right->left, execute);
    type = is_built_in_cmd(simple_cmd->cmd);
    built_in(simple_cmd, type);
}

void    built_in(t_simple_cmd *simple_cmd, t_simple_cmd_type type)
{
    const t_built_in_func fp[7] = {ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
    
    fp[type](simple_cmd);
}