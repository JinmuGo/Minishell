/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:53:21 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:54:08 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "envp_command.h"
#include "error.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		prt_err(ERR_ARGS, ERR_ARGS_NUM);
		exit(EXIT_FAILURE);
	}
	envp_init(envp);
	prompt();
	return (EXIT_SUCCESS);
}
