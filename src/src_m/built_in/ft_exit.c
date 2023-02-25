/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:19 by jgo               #+#    #+#             */
/*   Updated: 2023/02/25 18:48:02 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "error.h"

void ft_exit(t_simple_cmd *simple_cmd)
{
	const int	len = ft_arrlen((void **)simple_cmd->args);
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	if (len > 1)
	{
		exit_status = ft_atoi(simple_cmd->args[1]);
		if (exit_status == 0 && (ft_strncmp(simple_cmd->args[1], "0", 2) != 0))
		{
			ft_putstr_fd("exit\n", 2);
			print_error("exit: numeric argument required", 2);
			exit_status = 2;
		}
		else if (simple_cmd->args[2])
		{
			ft_putstr_fd("exit\n", 2);
			print_error("exit: too many arguments", -1);
			return ;
		}
	}

	// free_all_asset
	// clear_history();
	exit(exit_status);
}