/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_invoker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:08:05 by jgo               #+#    #+#             */
/*   Updated: 2023/02/12 12:33:11 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "envp_command.h"

t_meta *get_meta(void)
{
    return ((t_meta *)meta_receiver(META));
}

int     get_err_num(void)
{
    return (*(int *)meta_receiver(ERR_NUM));
}

t_hash_table *get_envp(void)
{
    return ((t_hash_table *)meta_receiver(ENVP));
}

t_list  *get_unlink_lst(void)
{
    return ((t_list *)meta_receiver(UNLINK));
}
