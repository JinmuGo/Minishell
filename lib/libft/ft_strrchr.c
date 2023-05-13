/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:53:33 by jgo               #+#    #+#             */
/*   Updated: 2023/04/10 17:21:44 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*str = s;

	while (*s++)
		;
	while (s != str)
	{
		s--;
		if (*s == (char)c)
			return ((char *)s);
	}
	return (NULL);
}
