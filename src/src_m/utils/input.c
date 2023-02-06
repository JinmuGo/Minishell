/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:06:38 by jgo               #+#    #+#             */
/*   Updated: 2023/02/06 20:37:08 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"

void	prompt(void)
{
	char	*line;
	t_tree	*tree;

	line = readline(MY_PROMPT);
	if (!line || ft_strncmp(line, "exit", 5) == 0)
		exit(EXIT_SUCCESS);
	tree = parser();
	// executor();
	// printf("%s \n", line);
	free(line);
	// system("leaks minishell");
	prompt();
}
