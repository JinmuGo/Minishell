/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_strchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:49:52 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 18:05:11 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

char	*ft_mini_strchr(const char *s, int c)
{
	size_t	i;
	char	quote;

	if ((char) c == '\0')
		return ((char *)(s + ft_strlen(s)));
	i = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			quote = is_same_quote(quote, s[i], 0);
		if (s[i] == (char)c && quote == 0)
			return ((char *)&s[i]);
		i++;
	}
	return ((void *)0);
}
