/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_all_ascii.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:46:19 by jgo               #+#    #+#             */
/*   Updated: 2023/02/17 16:04:25 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_add_all_ascii(const char *str)
{
	int	sum;
	int	i;

	if (str == NULL)
		return (-1);
	sum = 0;
	i = -1;
	while (str[++i])
		sum += str[i];
	return (sum);
}
