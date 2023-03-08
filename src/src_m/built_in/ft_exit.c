/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:19 by jgo               #+#    #+#             */
/*   Updated: 2023/03/08 14:12:06 by sanghwal         ###   ########seoul.kr  */
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
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}

int ft_exit(t_simple_cmd *simple_cmd)
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