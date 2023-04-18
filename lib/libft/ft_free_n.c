/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:51:37 by jgo               #+#    #+#             */
/*   Updated: 2023/02/25 18:07:11 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_n(int n, ...)
{
	va_list	ap;
	void	*target;
	int		i;

	va_start(ap, n);
	i = 0;
	while (i < n)
	{
		target = va_arg(ap, void *);
		free(target);
		i++;
	}
	va_end(ap);
}
