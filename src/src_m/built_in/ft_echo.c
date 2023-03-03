/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:25:28 by jgo               #+#    #+#             */
/*   Updated: 2023/03/03 22:39:15 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"
#include "meta_command.h"

// echo doesn't support other flags without -n 
// 다른 플래그 들은 무시된다.
// echo 바로 다음에 -n이 오지 않으면 출력하지 않는다. 

t_bool  n_option_confirm(char *target_str)
{
    int i;

    if (target_str[0] != '-')
        return (FT_FALSE);
    i = 1;
    while(target_str[i])
    {
        if (target_str[i] != 'n')
            return (FT_FALSE);
        i++;
    }
    return (FT_TRUE);
}

void    exec_echo (char **args, t_bool  n_option)
{
    int i;

    i = 0;
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1] != NULL)
            ft_putchar_fd(' ', STDOUT_FILENO); 
        i++;
    }
    if (!n_option)
        ft_putchar_fd('\n', STDOUT_FILENO);
}

void ft_echo(t_simple_cmd *simple_cmd)
{
    if (simple_cmd->args[1] == NULL)
        ft_putchar_fd('\n', STDOUT_FILENO);
    else if (n_option_confirm(simple_cmd->args[1]))
        exec_echo(&simple_cmd->args[2], FT_TRUE);
    else
        exec_echo(&simple_cmd->args[1], FT_FALSE);
    set_exit_status(EXIT_SUCCESS);
}