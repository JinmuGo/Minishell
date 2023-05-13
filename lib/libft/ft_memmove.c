/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:49:25 by jgo               #+#    #+#             */
/*   Updated: 2023/04/10 17:08:23 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	const unsigned char	*s;
	unsigned char		*tmp;

	if (!dest && !src)
		return (NULL);
	if (dest <= src)
	{
		s = (const unsigned char *)src;
		tmp = (unsigned char *)dest;
		while (len--)
			*tmp++ = *s++;
	}
	else
	{
		tmp = (unsigned char *)dest;
		tmp += len;
		s = (const unsigned char *)src;
		s += len;
		while (len--)
			*--tmp = *--s;
	}
	return (dest);
}
