/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:25:35 by jgo               #+#    #+#             */
/*   Updated: 2023/02/23 21:01:57 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "built_in.h"

// FT_ECHO = 0,
// FT_CD = 1,
// FT_PWD = 2,
// FT_EXPORT = 3,
// FT_UNSET = 4,
// FT_ENV = 5,
// FT_EXIT = 6,
// FT_EXTERNAL = 7
void    built_in(t_simple_cmd *simple_cmd, t_simple_cmd_type type)
{
    // const t_built_in_func fp[7] = {ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
    
    // fp[type](simple_cmd);
}