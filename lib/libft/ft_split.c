/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:06:51 by jgo               #+#    #+#             */
/*   Updated: 2023/02/09 19:00:52 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	total_word_count(char const *s, char c);
static size_t	cal_word_len(char const *s, char c, size_t i);
static t_bool	shift_i_judge_end(char const *s, char c, size_t *i);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	idx;
	size_t	word_size;

	if (!s)
		return ((void *)0);
	arr = malloc(sizeof(char *) * (total_word_count(s, c) + 1));
	if (!arr)
		return ((void *)0);
	i = 0;
	idx = 0;
	while (s[i])
	{
		if (shift_i_judge_end(s, c, &i))
			break ;
		word_size = cal_word_len(s, c, i);
		arr[idx] = malloc(sizeof(char) * word_size);
		if (!arr[idx])
			return (ft_free_all_arr(arr));
		ft_strlcpy(arr[idx++], &s[i], word_size);
		i += word_size - 1;
	}
	arr[idx] = 0;
	return (arr);
}

static size_t	total_word_count(char const *s, char c)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			cnt++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (cnt);
}

static size_t	cal_word_len(char const *s, char c, size_t start)
{
	size_t	end;

	end = start;
	while (s[end] && s[end] != c)
		end++;
	return (end - start + 1);
}

static t_bool	shift_i_judge_end(char const *s, char c, size_t *i)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	if (!s[*i])
		return (FT_TRUE);
	return (FT_FALSE);
}
