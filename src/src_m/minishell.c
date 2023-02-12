/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:53:21 by jgo               #+#    #+#             */
/*   Updated: 2023/02/12 13:00:49 by jgo              ###   ########.fr       */
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
	t_tree  *tree;
	char *token_1 = "echo";
	char *token_2 = "\'";
	char *token_3 = "$HOME";
	char *token_4 = "\'";
	char *test = "\"$SHELL\"\"$USER\"";
	char *test2 = "asdfasdf$";

	// signal(SIGQUIT, signal_process);
	// signal(SIGINT, signal_process);
	envp_init(envp);
	display(get_envp());
	// prompt();

	// shell_param_expand(test2);
	// shell_param_expand(token_1);
	// shell_param_expand(token_2);
	// shell_param_expand(token_3);
	// shell_param_expand(token_4);
	// system("leaks minishell");
	system("leaks minishell"); // ? 릭이 왜 안나지?
	return (EXIT_SUCCESS);
}
