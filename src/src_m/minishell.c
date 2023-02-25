/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:53:21 by jgo               #+#    #+#             */
/*   Updated: 2023/02/25 18:32:02 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "data_structure.h"
#include "expander.h"
#include "meta_command.h"
#include "envp_command.h"
#include "signal_controller.h"
#include "error.h"

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		print_error(ERR_ARGS, ERR_ARGS_NUM);
	envp_init(envp);
	prompt();
	return (EXIT_SUCCESS);
}
