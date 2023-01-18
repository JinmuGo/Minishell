/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:52:53 by jgo               #+#    #+#             */
/*   Updated: 2023/01/11 16:54:46 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen_printf(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static size_t	cal_num_len(size_t n, const size_t base_len)
{
	size_t	len;

	len = 1;
	while (n > (base_len - 1))
	{
		n /= base_len;
		len ++;
	}
	return (len);
}

char	*ft_itoa_base(size_t n, char *base)
{
	char			*str;
	size_t			len;
	const size_t	base_len = ft_strlen_printf(base);

	len = cal_num_len(n, base_len);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = base[n % base_len];
		n /= base_len;
		len--;
	}
	return (str);
}

int	ft_printf_strchr(const char *s, int c)
{
	int	i;

	if ((char) c == '\0')
		return ((int)ft_strlen_printf(s));
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}
