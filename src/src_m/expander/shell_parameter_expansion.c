/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:13:40 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 19:51:17 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "data_structure.h"
#include "envp_command.h"
#include "expander.h"
#include "meta_command.h"

t_bool	dollar_control(char c, char *rear, char next)
{
	if (c == DOLLAR)
	{
		if (rear != NULL && *rear != S_QUOTE)
			return (FT_TRUE);
		else if (next == ' ' || next == '\0')
			return (FT_FALSE);
		else if (rear == NULL)
			return (FT_TRUE);
	}
	return (FT_FALSE);
}

char	*expand_variable(char *dst, char *str, t_deque *deque, int i)
{
	int	tmp;
	int	j;

	j = 0;
	while (str[i++])
	{
		quote_control(deque, str[i - 1]);
		if (str[i - 1] == DOLLAR && str[i] == DOLLAR)
			double_dollar(dst, str, &i, &j);
		else if (\
			dollar_control(str[i - 1], (char *)deque->peek_rear(deque), str[i]) \
			&& is_shell_var(str[i]))
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
	dq_free(deque);
	return (dst);
}

int	cal_expand_len(char *str, t_deque *deque, int i)
{
	int	len;
	int	tmp;

	len = 0;
	while (str[i++])
	{
		quote_control(deque, str[i - 1]);
		if (str[i - 1] == DOLLAR && str[i] == DOLLAR)
			double_dollar(NULL, NULL, &i, &len);
		else if (\
			dollar_control(str[i - 1], (char *)deque->peek_rear(deque), str[i]) \
			&& is_shell_var(str[i]))
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
	dq_free(deque);
	return (len);
}

char	*shell_param_expand(char *str, t_list *next)
{
	int		expand_len;
	char	*dst;

	if (str == NULL)
		return (NULL);
	if (((str[0] == DOLLAR && str[1] == '\0' && next && \
		((((char *)(next->content))[0] == D_QUOTE || \
		((char *)(next->content))[0] == S_QUOTE)))))
		return (ft_strdup("\0"));
	expand_len = cal_expand_len(str, deque_init(ft_strlen(str)), 0);
	dst = ft_malloc(sizeof(char) * (expand_len + 1));
	dst = expand_variable(dst, str, deque_init(ft_strlen(str)), 0);
	free(str);
	return (dst);
}
