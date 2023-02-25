/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:21 by jgo               #+#    #+#             */
/*   Updated: 2023/02/25 18:32:29 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include <errno.h>
#include "meta_command.h"
#include "error.h"

void ft_pwd(t_simple_cmd *simple_cmd)
{
    char *cwd;

    (void)simple_cmd;
    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        set_exit_status(EXIT_FAILURE);
        print_error(strerror(errno), errno);
        return ;
    }
    ft_putstr_fd(cwd, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
    set_exit_status(EXIT_SUCCESS);
}