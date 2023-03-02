/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_invoker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:08:05 by jgo               #+#    #+#             */
/*   Updated: 2023/03/02 21:06:07 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "envp_command.h"

t_meta *get_meta(void)
{
    return ((t_meta *)meta_receiver(META, 0));
}

int     get_err_num(void)
{
    return (*(int *)meta_receiver(ERR_NUM, 0));
}

int     *get_exit_status(void)
{
    return ((int *)meta_receiver(EXIT_STATUS, 0));
}

t_hash_table *get_envp(void)
{
    return ((t_hash_table *)meta_receiver(ENVP, 0));
}

t_list  *get_unlink_lst(void)
{
    return ((t_list *)meta_receiver(UNLINK, 0));
}

void    set_err_num(int arg)
{
    meta_receiver(SET_ERR_NUM, arg);
}

void    set_exit_status(int arg)
{
    meta_receiver(SET_EXIT_STATUS, arg);
}

// pid_t   *get_pid(void) // get pid 
// {
//     meta_receiver(PID, 0, )
// }