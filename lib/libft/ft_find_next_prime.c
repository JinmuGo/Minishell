/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:04:31 by jgo               #+#    #+#             */
/*   Updated: 2023/04/10 17:09:48 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_prime(int nb)
{
	int	i;

	i = 2;
	while (i * i <= nb)
	{
		if (nb % i == 0)
			return (false);
		i++;
	}
	return (true);
}

int	ft_find_next_prime(int nb)
{
	if (nb < 2)
		return (2);
	if (is_prime(nb))
		nb++;
	while (!is_prime(nb))
		nb++;
	return (nb);
}
