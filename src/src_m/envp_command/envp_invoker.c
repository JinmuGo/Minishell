/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_invoker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:53:58 by jgo               #+#    #+#             */
/*   Updated: 2023/02/13 14:30:32 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"

void	set_envp_elem(const char *key,const char *val)
{
	envp_receiver(SET, key, val);
}

t_hash_elem	*get_envp_elem(const char *key)
{
	return (envp_receiver(GET, key, NULL));
}

void	del_envp_elem(const char *key)
{
	envp_receiver(DEL, key, NULL);
}
