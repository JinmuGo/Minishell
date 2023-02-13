/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:06:38 by jgo               #+#    #+#             */
/*   Updated: 2023/02/13 14:51:16 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "expander.h"

void    prompt()
{
	char *line;
	char *tmp;

	line = readline(MY_PROMPT);
	if (!line || ft_strncmp(line, "exit", 5) == 0)
		exit(EXIT_SUCCESS);
	// parser();
	// executor();
	tmp = shell_param_expand(line);
	printf("%s\n", tmp);
	free(line);
	prompt();
}