/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:44:35 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:39:15 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"
#include "meta_command.h"

void	double_dollar(char *dst, char *str, int *i, int *j)
{
	if (dst && str)
	{
		dst[(*j)++] = str[*i - 1];
		(*i)++;
		dst[(*j)++] = str[*i - 1];
	}
	else
	{
		(*j) += 2;
		(*i)++;
	}
}

int	expand_and_dup(char *dst, char *key, int j)
{
	const t_hash_elem	*elem = get_envp_elem(key);
	char				*expanded;
	int					i;

	expanded = NULL;
	if (key[0] == '?')
		expanded = ft_itoa(*(get_exit_status()));
	if (elem)
		expanded = elem->val;
	if (expanded == NULL)
	{
		free(key);
		return (0);
	}
	i = 0;
	while (expanded[i])
		dst[j++] = expanded[i++];
	if (key[0] == '?')
		free(expanded);
	free(key);
	return (j);
}

int	try_expand_and_cal_len(char *str, int i, int tmp)
{
	const char			*dst = ft_substr(str, tmp, i - tmp);
	const t_hash_elem	*elem = get_envp_elem(dst);
	char				*tmp_str;
	int					len;

	len = 0;
	if (dst[0] == '?')
	{
		tmp_str = ft_itoa(*(get_exit_status()));
		len = ft_strlen(tmp_str);
		free((void *)tmp_str);
	}
	if (elem == NULL)
	{
		free((void *)dst);
		return (len);
	}
	else
		len = elem->val_len;
	free((void *)dst);
	return (len);
}

char	is_same_quote(char quote, char c, char initial)
{
	if (quote != initial)
	{
		if (quote == c)
			return (initial);
		else
			return (quote);
	}
	else
		return (c);
}

t_bool	is_in_quote(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			return (FT_TRUE);
		i++;
	}
	return (FT_FALSE);
}
