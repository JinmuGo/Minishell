/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:53:21 by jgo               #+#    #+#             */
/*   Updated: 2023/02/27 17:32:37 by sanghwal         ###   ########seoul.kr  */
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

int main(int argc, char **argv, char **envp)
{
	t_tree  *tree;
	
	envp_init(envp);
	prompt();

	system("leaks minishell");
	return (EXIT_SUCCESS);
}
