/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:47:50 by jgo               #+#    #+#             */
/*   Updated: 2022/11/17 11:06:00 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cal_num_len(int n);

char	*ft_itoa(int n)
{
	unsigned int	tmp;
	char			*num;
	int				len;
	int				for_minus;

	for_minus = 0;
	len = cal_num_len(n);
	num = malloc(sizeof(char) * (len + 1));
	if (!num)
		return ((void *)0);
	tmp = n;
	if (n < 0)
	{
		tmp *= -1;
		num[0] = '-';
		for_minus++;
	}
	num[len] = '\0';
	while (len-- > for_minus)
	{
		num[len] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (num);
}

static size_t	cal_num_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
