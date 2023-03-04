/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:21 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 11:39:02 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include <errno.h>
#include "meta_command.h"
#include "error.h"

int ft_pwd(t_simple_cmd *simple_cmd)
{
    char *cwd;

    (void)simple_cmd;
    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        prt_err(strerror(errno), errno);
        return (EXIT_FAILURE);
    }
    ft_putstr_fd(cwd, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
    return (EXIT_SUCCESS);
}