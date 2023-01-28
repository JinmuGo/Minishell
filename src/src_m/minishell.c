/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:53:21 by jgo               #+#    #+#             */
/*   Updated: 2023/01/28 15:47:05 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_tree  *tree;

    while (LOOP)
    {
        line = readline("> ");

        printf("line : %s\n", line);
        free(line);
    }

    return (EXIT_SUCCESS);
}