/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:19 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 11:37:19 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "error.h"

int ft_exit(t_simple_cmd *simple_cmd)
{
	const int	len = ft_arrlen((void **)simple_cmd->args);
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	if (len > 1)
	{
		exit_status = ft_atoi(simple_cmd->args[1]);
		if (exit_status == 0 && (ft_strncmp(simple_cmd->args[1], "0", 2) != 0))
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			prt_err("exit: numeric argument required", 255);
			exit_status = 255;
		}
		else if (simple_cmd->args[2])
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			prt_err("exit: too many arguments", EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_status);
}