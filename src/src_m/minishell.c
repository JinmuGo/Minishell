/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:53:21 by jgo               #+#    #+#             */
/*   Updated: 2023/02/24 16:16:52 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "data_structure.h"
#include "expander.h"
#include "meta_command.h"
#include "envp_command.h"

int main(int argc, char **argv, char **envp)
{
	t_tree	*tree;

	envp_init(envp);
	// display(get_envp());
	set_status(0);
	signal(SIGQUIT, signal_process);
	signal(SIGINT, signal_process);
	prompt();

	system("leaks minishell");
	return (EXIT_SUCCESS);
}
