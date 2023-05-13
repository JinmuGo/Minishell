/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:29:22 by jgo               #+#    #+#             */
/*   Updated: 2023/04/10 17:08:23 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup(const char **src)
{
	const size_t	len = ft_arrlen((void *)src);
	char			**dst;
	size_t			i;

	if (len == 0)
		return (NULL);
	dst = ft_malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (src[++i])
		dst[i] = ft_strdup(src[i]);
	dst[i] = NULL;
	return (dst);
}
