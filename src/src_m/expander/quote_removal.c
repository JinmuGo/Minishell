/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:42:45 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:39:22 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "data_structure.h"
#include "expander.h"

char	is_same_quote_len(char quote, char c, int *len, char initial)
{
	if (quote != initial)
	{
		if (quote == c)
			return (initial);
		else
		{
			(*len)++;
			return (quote);
		}
	}
	else
		return (c);
}

int	cal_remove_len(char *str)
{
	char	quote;
	int		len;
	int		i;

	len = 0;
	i = -1;
	quote = 1;
	while (str[++i])
	{
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			quote = is_same_quote_len(quote, str[i], &len, 0);
		else
		{
			if (quote)
				len++;
		}
	}
	return (len);
}

char	check_quote(char quote, char c, char *dst, int *j)
{
	if (quote != 1)
	{
		if (quote == c)
			return (1);
		else
		{
			dst[(*j)++] = c;
			return (quote);
		}
	}
	else
		return (c);
}

char	*remove_quote(char *dst, char *str)
{
	char	quote;
	int		j;
	int		i;

	j = 0;
	i = -1;
	quote = 1;
	while (str[++i])
	{
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			quote = check_quote(quote, str[i], dst, &j);
		else
		{
			if (quote)
				dst[j++] = str[i];
		}
	}
	dst[j] = '\0';
	return (dst);
}

char	*quote_removal(char *str)
{
	const int	len = cal_remove_len(str);
	char		*dst;

	dst = ft_malloc(sizeof(char) * (len + 1));
	dst = remove_quote(dst, str);
	free(str);
	return (dst);
}
