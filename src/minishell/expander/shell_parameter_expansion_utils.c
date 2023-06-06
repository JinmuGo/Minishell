/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:16:31 by jgo               #+#    #+#             */
/*   Updated: 2023/05/14 08:54:36 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

bool	is_shell_var(char c)
{
	if (c == '_' || c == '?')
		return (true);
	if (ft_isspecial(c) || c == '\0')
		return (false);
	return (true);
}

void	quote_control(const t_deque *deque, char c)
{
	char	*tmp;

	if (c == S_QUOTE || c == D_QUOTE)
	{
		tmp = ((char *)(deque->peek_front((t_deque *)deque)));
		if (tmp == NULL || *tmp != c)
		{
			tmp = ft_malloc(sizeof(char));
			*tmp = c;
			deque->push_front((t_deque *)deque, tmp);
		}
		else
		{
			tmp = (char *)deque->pop_front((t_deque *)deque);
			if (tmp)
				free(tmp);
		}
	}
}

void	adjust_param_idx(char *str, int *i)
{
	if (str[*i] == '?' || ft_isdigit(str[*i]))
		(*i)++;
	else
		while (\
			is_shell_var(str[*i]) && (str[*i] != S_QUOTE && str[*i] != D_QUOTE))
			(*i)++;
}
