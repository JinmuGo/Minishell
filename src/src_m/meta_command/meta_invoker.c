/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_invoker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:08:05 by jgo               #+#    #+#             */
/*   Updated: 2023/03/08 17:06:31 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "envp_command.h"

t_meta *get_meta(void)
{
    return ((t_meta *)meta_receiver(META, 0, NULL));
}

int     get_err_num(void)
{
    return (*(int *)meta_receiver(ERR_NUM, 0, NULL));
}

int     *get_exit_status(void)
{
    return ((int *)meta_receiver(EXIT_STATUS, 0, NULL));
}

t_hash_table *get_envp(void)
{
    return ((t_hash_table *)meta_receiver(ENVP, 0, NULL));
}

t_list  **get_unlink_lst(void)
{
    return ((t_list **)meta_receiver(UNLINK, 0, NULL));
}

void    set_err_num(int arg)
{
    meta_receiver(SET_ERR_NUM, arg, NULL);
}

void    set_exit_status(int arg)
{
    meta_receiver(SET_EXIT_STATUS, arg, NULL);
}

char    *get_cur_dir(void)
{
    return (meta_receiver(GET_CUR_DIR, 0, NULL));
}

void    set_cur_dir(char *str)
{
    meta_receiver(SET_CUR_DIR, 0, str);
}