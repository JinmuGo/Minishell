/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:21 by jgo               #+#    #+#             */
/*   Updated: 2023/03/06 23:13:18 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include <errno.h>
#include "meta_command.h"
#include "error.h"

// 만약 cwd를 구할 수 있다면 이전 cwd를 free하고 새로운 cwd를 할당. 
// 만약 cwd를 구할 수 없다면 이전 cwd를 출력. 
int ft_pwd(t_simple_cmd *simple_cmd)
{
    static  char *prev_cwd;
    char    *cwd;

    cwd = get_cur_dir();
    if (cwd)
    {
        ft_putstr_fd(cwd, STDOUT_FILENO);
        if (prev_cwd)
            free(prev_cwd);
        prev_cwd = ft_strdup(cwd);
    }
    else
        ft_putstr_fd(prev_cwd, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
    return (EXIT_SUCCESS);
}