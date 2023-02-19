/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_receiver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 11:16:11 by jgo               #+#    #+#             */
/*   Updated: 2023/02/12 12:49:52 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"
#include "utils.h"

void    *meta_receiver(t_meta_flags flag)
{
    t_meta *meta;

    meta = singleton();
    if (flag == META)
        return (meta);
    else if (flag == ERR_NUM)
        return (&meta->err);
    else if (flag == ENVP)
        return (meta->envp);
    else if (flag == UNLINK)
        return (meta->unlink_lst);
    return (NULL);
}
