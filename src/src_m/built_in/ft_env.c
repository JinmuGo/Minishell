/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:18 by jgo               #+#    #+#             */
/*   Updated: 2023/02/25 18:32:22 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"
#include "meta_command.h"
#include "error.h"
#include <errno.h>

void ft_env(t_simple_cmd *simple_cmd)
{
	const int	len = ft_arrlen((void **)simple_cmd->args);

	if (len == 1)
	{
		print_envp_elem(NULL);
		set_exit_status(EXIT_SUCCESS);
	}
	else
		print_error("env: doesn't take args", ERR_ARGS_NUM);
}
