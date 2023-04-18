/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:00:46 by jgo               #+#    #+#             */
/*   Updated: 2022/11/17 11:07:13 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const size_t	needle_len = ft_strlen(needle);
	const size_t	haystack_len = ft_strlen(haystack);
	size_t			haystack_i;

	if (needle[0] == '\0')
		return ((char *)haystack);
	haystack_i = 0;
	while (haystack[haystack_i] && haystack_len - haystack_i >= needle_len
		&& haystack_i + needle_len <= len)
	{
		if (haystack[haystack_i] == needle[0])
		{	
			if (!ft_strncmp(&haystack[haystack_i], needle, needle_len))
				return ((char *)&haystack[haystack_i]);
		}
		haystack_i++;
	}
	return (0);
}
