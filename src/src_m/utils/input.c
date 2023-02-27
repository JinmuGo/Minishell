/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:06:38 by jgo               #+#    #+#             */
/*   Updated: 2023/02/27 17:31:14 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "signal_controller.h"

void	prompt(void)
{
	char *line;
	const char *_prompt = make_prompt();
	t_tree	*tree;
	struct sigaction s_int;
	struct sigaction s_quit;

	signal_controller(&s_int, &s_quit, SIG_INIT);
	line = readline(_prompt);
	if (!line || ft_strncmp(line, "exit", 5) == 0)
	{
		clear_history();
		exit(EXIT_SUCCESS);
	}
	tree = parser(line);
	if (line && *line)
		add_history(line);
	expander(tree->root);
	print_tree_node(tree->root, 0);
	// executor();
	free(line);
	free((void *)_prompt);
	system("leaks minishell");
	prompt();
}
