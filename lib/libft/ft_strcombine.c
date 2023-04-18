/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcombine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:25:49 by jgo               #+#    #+#             */
/*   Updated: 2023/02/08 18:16:52 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcombine(int n, ...)
{
	va_list	ap;	
	char	*tmp;
	char	*arg;
	char	*str;
	int		i;

	va_start(ap, n);
	i = 0;
	str = va_arg(ap, char *);
	while (i < n - 1)
	{
		arg = va_arg(ap, char *);
		tmp = str;
		str = ft_strjoin(str, arg);
		if (i != 0)
			free(tmp);
		i++;
	}
	va_end(ap);
	return (str);
}
