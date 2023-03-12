/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_invoker2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:48:14 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 18:02:00 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "envp_command.h"

void	set_err_num(int arg)
{
	meta_receiver(SET_ERR_NUM, arg, NULL);
}

void	set_exit_status(int arg)
{
	meta_receiver(SET_EXIT_STATUS, arg, NULL);
}

char	*get_cur_dir(void)
{
	return (meta_receiver(GET_CUR_DIR, 0, NULL));
}

void	set_cur_dir(char *str)
{
	meta_receiver(SET_CUR_DIR, 0, str);
}
