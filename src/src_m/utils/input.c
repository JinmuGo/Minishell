/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:06:38 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 10:13:21 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "signal_controller.h"
#include "executor.h"
#include "meta_command.h"

void	prompt(void)
{
	char *line;
	const char *_prompt = make_prompt();
	t_tree	*tree;
	t_meta	*meta;

	meta = get_meta();
	signal_controller(SIG_INIT);
	line = readline(_prompt);
	if (!line)
	{
		printf("exit\n");
		clear_history();
		// free_all_asset
		exit(EXIT_SUCCESS);
	}
	tree = parser(line);
	printf("err code : %d\n", meta->err);
	if (line && *line)
		add_history(line);
	expander(tree);
	print_tree_node(tree->root, 0, "root");
	executor(tree);
	// print_tree_node(tree->root, 0, "root");
	meta->err = ERR_NOTHING;
	expander(tree->root);
	print_tree_node(tree->root, 0);
	// executor();
	free(line);
	free((void *)_prompt);
	// system("leaks minishell");
	prompt();
}
