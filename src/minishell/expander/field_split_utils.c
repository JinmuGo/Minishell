/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:40:33 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 20:31:37 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

t_list	*split_node(char *str, const int str_len)
{
	t_list	*lst;
	int		i;
	int		len;
	char	quote;

	i = -1;
	len = 0;
	lst = NULL;
	quote = 0;
	while (++i <= str_len)
	{
		if ((str[i] == S_QUOTE || str[i] == D_QUOTE || \
			str[i] == '$' || str[i] == '\0') && quote == 0 && i)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i - len, len)));
			len = 0;
		}
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			quote = is_same_quote(quote, str[i], 0);
		len++;
	}
	if (lst)
		return (lst);
	else
		return (NULL);
}

void	fill_arg(t_simple_cmd *cmd, char **args, char **tmp, int cur_idx)
{
	int	i;
	int	j;
	int	idx;

	i = -1;
	j = -1;
	idx = 0;
	while (++i < cur_idx)
		args[idx++] = ft_strdup(cmd->args[i]);
	while (tmp[++j])
		args[idx++] = ft_strdup(tmp[j]);
	while (cmd->args[++i])
		args[idx++] = ft_strdup(cmd->args[i]);
	args[idx] = NULL;
}

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

char	*ft_imin_strchr(const char *s, int c)
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
		if (s[i] == (char)c && quote)
			return ((char *)&s[i]);
		i++;
	}
	return ((void *)0);
}
