/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:06:38 by jgo               #+#    #+#             */
/*   Updated: 2023/02/25 20:55:07 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "signal_controller.h"
#include "executor.h"

void	prompt(void)
{
	char *line;
	const char *_prompt = make_prompt();
	t_tree	*tree;
	struct sigaction s_int;
	struct sigaction s_quit;

	signal_controller(&s_int, &s_quit, SIG_INIT);
	line = readline(_prompt);
	if (!line)
	{
		printf("exit\n");
		clear_history();
		// free_all_asset
		exit(EXIT_SUCCESS);
	}
	tree = parser(line);
	if (line && *line)
		add_history(line);
	expander(tree);
	print_tree_node(tree->root, 0);
	executor(tree);
	print_tree_node(tree->root, 0);
	free(line);
	free((void *)_prompt);
	prompt();
}
