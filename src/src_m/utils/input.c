/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:06:38 by jgo               #+#    #+#             */
/*   Updated: 2023/03/07 20:50:15 by jgo              ###   ########.fr       */
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
#include "data_structure.h"
#include "error.h"

void	prompt(void)
{
	char *line;
	t_tree	tree;
	t_meta	*meta;

	meta = get_meta();
	signal_controller(SIG_INIT);
	tree_init(&tree);
	while (FT_TRUE)
	{
		meta->cur_dir = redef_cur_dir(meta->cur_dir);
		meta->prompt = make_prompt(meta->prompt);
		line = readline(meta->prompt);
		if (!line)
		{
			printf("exit\n");
			clear_history();
			// free_all_asset
			exit(EXIT_SUCCESS);
		}
		if (line && *line)
			add_history(line);
		parser(line, &tree);
		print_tree_node(tree.root, 0, "root");
		if (meta->err == ERR_NOTHING)
		{
			expander(&tree);
			executor(&tree);
		}
		print_tree_node(tree.root, 0, "root");
		err_handler(meta);
		clear_asset(line, &tree, meta);
		meta->err = ERR_NOTHING;
	}
}

// leak이 어디서 나는거야?!
