/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:47:10 by jgo               #+#    #+#             */
/*   Updated: 2023/01/28 15:56:53 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

t_meta  *get_meta(void)
{
	static t_meta *meta;

	if (meta != NULL)
		return (meta);
	meta = ft_malloc(sizeof(t_meta));
	return (meta);
}