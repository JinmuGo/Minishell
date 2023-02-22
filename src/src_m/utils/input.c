/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:06:38 by jgo               #+#    #+#             */
/*   Updated: 2023/02/22 15:51:37 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"

void	prompt(void)
{
	char *line;
	char *tmp;
	const char *_prompt = make_prompt();
	t_tree	*tree;

	line = readline(_prompt);
	if (!line || ft_strncmp(line, "exit", 5) == 0)
		exit(EXIT_SUCCESS);
	tree = parser(line);
	// executor();
	expander(tree->root);
	print_tree_node(tree->root, 0);
	free(line);
	free((void *)_prompt);
	prompt();
}
