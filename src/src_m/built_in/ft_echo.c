/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:25:28 by jgo               #+#    #+#             */
/*   Updated: 2023/03/16 20:13:54 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"
#include "meta_command.h"
#include "error.h"

t_bool	n_option_confirm(char *target_str)
{
	int	i;

	if (target_str == NULL)
		return (FT_FALSE);
	if (target_str[0] != '-')
		return (FT_FALSE);
	if (target_str[0] == '-' && target_str[1] == '\0')
		return (FT_FALSE);
	i = 1;
	while (target_str[i])
	{
		if (target_str[i] != 'n')
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}

int	exec_echo(char **args, t_bool n_option, int i)
{
	char	tmp;
	int		rv;

	rv = FT_TRUE;
	while (args[i])
	{
		rv = write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL && rv != -1)
		{
			tmp = ' ';
			rv = write(STDOUT_FILENO, &tmp, 1);
		}
		if (prt_sc_err(rv) == FT_FALSE)
			return (rv);
		i++;
	}
	if (!n_option)
	{
		tmp = '\n';
		rv = write(STDOUT_FILENO, &tmp, 1);
	}
	if (prt_sc_err(rv) == FT_FALSE)
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
		rv = exec_echo(&simple_cmd->args[i], FT_TRUE, 0);
	else
		rv = exec_echo(&simple_cmd->args[i], FT_FALSE, 0);
	if (rv == -1)
		rv = EXIT_FAILURE;
	else
		rv = EXIT_SUCCESS;
	return (rv);
}
