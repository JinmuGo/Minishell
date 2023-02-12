/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_receiver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:18:49 by jgo               #+#    #+#             */
/*   Updated: 2023/02/12 12:51:25 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"
#include "meta_command.h"

t_hash_elem *envp_receiver(t_envp_flags flag, char *key, char *val)
{
    t_hash_table *envp;
    
    envp = get_envp();
    if (flag == SET)
        hash_insert(envp, key, val);
    else if (flag == GET)
        return (hash_get(envp, key));
    else if (flag == DEL)
       hash_delete(envp, key);
    return (NULL);
}