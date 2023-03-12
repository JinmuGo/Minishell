/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_invoker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:08:05 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:48:32 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "envp_command.h"

t_meta	*get_meta(void)
{
	return ((t_meta *)meta_receiver(META, 0, NULL));
}

int	get_err_num(void)
{
	return (*(int *)meta_receiver(ERR_NUM, 0, NULL));
}

int	*get_exit_status(void)
{
	return ((int *)meta_receiver(EXIT_STATUS, 0, NULL));
}

t_hash_table	*get_envp(void)
{
	return ((t_hash_table *)meta_receiver(ENVP, 0, NULL));
}

t_list	**get_unlink_lst(void)
{
	return ((t_list **)meta_receiver(UNLINK, 0, NULL));
}
