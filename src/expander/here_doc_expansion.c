/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:42:24 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:34:44 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

static char	*here_doc_expand_variable(char *dst, char *str)
{
	int	tmp;
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i++])
	{
		if (str[i - 1] == DOLLAR && str[i] == DOLLAR)
			double_dollar(dst, str, &i, &j);
		else if (str[i - 1] == '$' && is_shell_var(str[i]))
		{
			tmp = i;
			adjust_param_idx(str, &i);
			tmp = expand_and_dup(dst, ft_substr(str, tmp, i - tmp), j);
			if (tmp != 0)
				j = tmp;
		}
		else
			dst[j++] = str[i - 1];
	}
	dst[j] = '\0';
	return (dst);
}

static int	here_doc_cal_expand_len(char *str)
{
	int	len;
	int	tmp;
	int	i;

	len = 0;
	i = 0;
	while (str[i++])
	{
		if (str[i - 1] == DOLLAR && str[i] == DOLLAR)
			double_dollar(NULL, NULL, &i, &len);
		else if (str[i] == '$' && is_shell_var(str[i]))
		{
			tmp = i;
			adjust_param_idx(str, &i);
			tmp = try_expand_and_cal_len(str, i, tmp);
			if (tmp > 0)
				len += tmp;
		}
		else
			len++;
	}
	return (len);
}

char	*here_doc_expand(char *str)
{
	const int	expand_len = here_doc_cal_expand_len(str);
	char		*dst;

	dst = ft_malloc(sizeof(char) * (expand_len + 1));
	dst = here_doc_expand_variable(dst, str);
	free(str);
	return (dst);
}
