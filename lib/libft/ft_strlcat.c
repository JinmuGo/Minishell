/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:27:16 by jgo               #+#    #+#             */
/*   Updated: 2022/11/17 11:06:56 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	const size_t	dest_len = ft_strlen(dest);
	const size_t	src_len = ft_strlen(src);
	size_t			i;

	if (size <= dest_len)
		return (src_len + size);
	i = 0;
	while (src[i] && dest_len + i + 1 < size)
	{
		dest[i + dest_len] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}
