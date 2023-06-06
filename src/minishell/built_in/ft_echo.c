/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:25:28 by jgo               #+#    #+#             */
/*   Updated: 2023/05/14 08:54:36 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"
#include "meta_command.h"
#include "error.h"

bool	n_option_confirm(char *target_str)
{
	int	i;

	if (target_str == NULL)
		return (false);
	if (target_str[0] != '-')
		return (false);
	if (target_str[0] == '-' && target_str[1] == '\0')
		return (false);
	i = 1;
	while (target_str[i])
	{
		if (target_str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	exec_echo(char **args, bool n_option, int i)
{
	char	tmp;
	int		rv;

	rv = true;
	while (args[i])
	{
		rv = write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL && rv != -1)
		{
			tmp = ' ';
			rv = write(STDOUT_FILENO, &tmp, 1);
		}
		if (prt_sc_err(rv) == false)
			return (rv);
		i++;
	}
	if (!n_option)
	{
		tmp = '\n';
		rv = write(STDOUT_FILENO, &tmp, 1);
	}
	if (prt_sc_err(rv) == false)
		return (rv);
	return (rv);
}

int	ft_echo(t_simple_cmd *simple_cmd)
{
	int	rv;
	int	i;

	i = 0;
	if (simple_cmd->args[1] == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	while (n_option_confirm(simple_cmd->args[++i]))
		continue ;
	if (i > 1)
		rv = exec_echo(&simple_cmd->args[i], true, 0);
	else
		rv = exec_echo(&simple_cmd->args[i], false, 0);
	if (rv == -1)
		rv = EXIT_FAILURE;
	else
		rv = EXIT_SUCCESS;
	return (rv);
}
