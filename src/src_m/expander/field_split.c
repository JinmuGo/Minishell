/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:44:21 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 20:25:08 by jgo              ###   ########.fr       */
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

void	arg_field_split_proc(\
	t_simple_cmd *cmd, char **splited_cmd, const int origin_len)
{
	const int	len = ft_arrlen((void *)splited_cmd);
	char		**args;
	int			i;
	int			idx;

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

void	cmd_field_split(t_simple_cmd *cmd, const char *dup_cmd)
{
	char	**splited_arr;
	int		origin_len;

	if (ft_imin_strchr(dup_cmd, DOLLAR))
		return ;
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
