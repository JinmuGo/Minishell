/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:22 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 17:44:30 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "error.h"
#include "meta_command.h"
#include "envp_command.h"
#include "built_in.h"

int ft_unset(t_simple_cmd *simple_cmd)
{
	t_bool	is_fail;
    int	i;
	int	j;

	if (simple_cmd->args[1] == NULL)
		return (EXIT_SUCCESS);
	is_fail = EXIT_SUCCESS;
	if (ft_isdigit(simple_cmd->args[1][0]))
	{
        prt_built_in_err("unset ", simple_cmd->args[1], ERR_INVALID_IDENT, EXIT_FAILURE);
		is_fail = EXIT_FAILURE;
	}
    i = -1;
	while (simple_cmd->args[++i])
	{
		j = -1;
		while (simple_cmd->args[i][++j])
			if (is_valid_params(simple_cmd->args[i][j]) == FT_FALSE)
			{
				prt_built_in_err("unset ", simple_cmd->args[i], ERR_INVALID_IDENT, EXIT_FAILURE);
				is_fail = EXIT_FAILURE;
			}
			else
				del_envp_elem(simple_cmd->args[i]);
	}
	return (is_fail);
}