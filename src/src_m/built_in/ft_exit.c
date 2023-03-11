/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:19 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 11:48:05 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "error.h"

static t_bool	judge_args(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}

int	ft_exit(t_simple_cmd *simple_cmd)
{
	const int	len = ft_arrlen((void **)simple_cmd->args);
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	if (len > 1)
	{
		exit_status = ft_atoi(simple_cmd->args[1]);
		if (!judge_args(simple_cmd->args[1]))
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			prt_err("exit: numeric argument required", 255);
			exit_status = 255;
			exit(exit_status);
		}
		else if (simple_cmd->args[2])
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			prt_err("exit: too many arguments", EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(exit_status);
}
