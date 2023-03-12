/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:51:27 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:34:23 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

/**
 * @brief check built_in function in cmd
 * 
 * @param cmd in t_simple_cmd
 * @return t_simple_cmd_type
 */
t_simple_cmd_type	is_built_in_cmd(char *cmd)
{
	const char	*built_in[7] = {\
		"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmd, built_in[i], ft_strlen(built_in[i])) == 0)
			return (i);
		i++;
	}
	return (FT_EXTERNAL);
}
