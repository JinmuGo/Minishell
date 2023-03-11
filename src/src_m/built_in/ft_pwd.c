/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:21 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 12:01:14 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include <errno.h>
#include "meta_command.h"
#include "error.h"

int	ft_pwd(t_simple_cmd *simple_cmd)
{
	static char	*prev_cwd;
	char		*cwd;

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
