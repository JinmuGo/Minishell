/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:53:21 by jgo               #+#    #+#             */
/*   Updated: 2023/01/28 15:22:54 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "declaration.h"

int main(int argc, char **argv, char **envp)
{
    char *line;    

    while (LOOP)
    {
        line = readline("> ");
        printf("line : %s\n", line);
        free(line);
    }

    return (EXIT_SUCCESS);
}