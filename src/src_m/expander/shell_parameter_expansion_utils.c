/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:16:31 by jgo               #+#    #+#             */
/*   Updated: 2023/02/19 18:06:25 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

t_bool is_shell_var(char c)
{
    if (c == '_' || c == '?')
        return (FT_TRUE);
    if (ft_isspecial(c) || c == '\0')
        return (FT_FALSE);
    return (FT_TRUE);
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
