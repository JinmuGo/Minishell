/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_receiver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:18:49 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 11:33:23 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"
#include "meta_command.h"

t_hash_elem	*envp_receiver(\
	t_envp_flags flag, const char *key, const char *val, const char *option)
{
	t_hash_table	*envp;

	envp = get_envp();
	if (flag == SET)
		hash_insert(envp, key, val);
	else if (flag == GET)
		return (hash_get(envp, key));
	else if (flag == DEL)
		hash_delete(envp, key);
	else if (flag == PRINT)
		hash_print_all(option, envp);
	return (NULL);
}
