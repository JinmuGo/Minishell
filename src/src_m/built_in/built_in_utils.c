/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:17:20 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 11:44:49 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_valid_params(char c)
{
	if (c == '_')
		return (FT_TRUE);
	if (ft_isspecial(c) || c == '\0')
		return (FT_FALSE);
	return (FT_TRUE);
}
