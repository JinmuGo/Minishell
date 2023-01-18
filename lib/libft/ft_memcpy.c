/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:01:53 by jgo               #+#    #+#             */
/*   Updated: 2022/11/17 11:06:13 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*s = src;
	char		*tmp;
	size_t		i;

	if (!n || dest == src)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	tmp = dest;
	while (i < n)
	{
		tmp[i] = s[i];
		i++;
	}
	return (dest);
}
