/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:06:38 by jgo               #+#    #+#             */
/*   Updated: 2023/02/28 22:14:39 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "signal_controller.h"
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
	if (!line || ft_strncmp(line, "exit", 5) == 0)
	{
		clear_history();
		exit(EXIT_SUCCESS);
	}
	tree = parser(line);
	printf("err code : %d\n", meta->err);
	if (line && *line)
		add_history(line);
	meta->err = ERR_NOTHING;
	expander(tree->root);
	print_tree_node(tree->root, 0);
	// executor();
	free(line);
	free((void *)_prompt);
	// system("leaks minishell");
	prompt();
}
