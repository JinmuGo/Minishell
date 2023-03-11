/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:44:21 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 11:08:04 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

static void	cmd_field_split_proc(\
	t_simple_cmd *cmd, char **splited_cmd, const int origin_len)
{
	const int	len = ft_arrlen((void *)splited_cmd);
	char		**args;
	int			idx;
	int			i;

	if (*splited_cmd == NULL)
		return ;
	free(cmd->cmd);
	cmd->cmd = ft_strdup(splited_cmd[0]);
	args = ft_malloc(sizeof(char *) * (len + origin_len));
	i = -1;
	idx = 0;
	while (++i < len)
		args[idx++] = ft_strdup(splited_cmd[i]);
	i = 0;
	while (cmd->args[++i])
		args[idx++] = ft_strdup(cmd->args[i]);
	ft_free_all_arr(cmd->args);
	args[idx] = NULL;
	cmd->args = args;
}

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
			str[i] == '$' || str[i] == '\0') && quote == 0)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i - len, len)));
			len = 0;
		}
		if (str[i] == '\'' || str[i] == '\"')
			quote = is_same_quote(quote, str[i], &len, 0);
		len++;
	}
	if (lst)
		return (lst);
	else
		return (NULL);
}

static void	fill_arg(t_simple_cmd *cmd, char **args, char **tmp, int cur_idx)
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

void	cmd_field_split(t_simple_cmd *cmd)
{
	char	**splited_arr;
	int		origin_len;
	int		i;

	splited_arr = ft_split(cmd->cmd, ' ');
	origin_len = ft_arrlen((void *)cmd->args);
	cmd_field_split_proc(cmd, splited_arr, origin_len);
	ft_free_all_arr(splited_arr);
}

void	arg_field_split(\
	t_simple_cmd *cmd, char *str, int cur_idx, const int origin_len)
{
	char	**tmp;
	char	**args;
	int		len;

	tmp = ft_split(str, ' ');
	if (*tmp == NULL)
	{
		ft_free_all_arr(tmp);
		return ;
	}
	len = ft_arrlen((void *)tmp);
	args = ft_malloc(sizeof(char *) * (len + origin_len));
	fill_arg(cmd, args, tmp, cur_idx);
	ft_free_all_arr(cmd->args);
	ft_free_all_arr(tmp);
	cmd->args = args;
}
