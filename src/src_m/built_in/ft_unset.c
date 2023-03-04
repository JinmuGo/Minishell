/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:22 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 12:02:27 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

int ft_unset(t_simple_cmd *simple_cmd)
{
    int	i;

	if (simple_cmd->args[1] == NULL)
		return (EXIT_SUCCESS);
}