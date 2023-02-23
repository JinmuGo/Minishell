/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:54:14 by jgo               #+#    #+#             */
/*   Updated: 2022/12/13 14:43:41 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static	enum e_exec	is_exec(char *abs_path, char **whole_cmd)
{
	if (abs_path)
	{
		if (access(abs_path, X_OK) == 0)
			return (POSSIBLE);
		else
			return (IMPOSSIBLE);
	}
	else
	{
		if (access(*whole_cmd, X_OK) == 0 && ft_strchr(*whole_cmd, '/'))
			return (POSSIBLE);
		else
			return (IMPOSSIBLE);
	}
}

static char	**get_path_arr(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		return (ft_split(&envp[i][5], ':'));
	else
		return (NULL);
}

char	*make_abs_path(char *cmd, const char **path_arr)
{
	char	*rv;
	char	*tmp;
	int		i;

	if (!path_arr || ft_strchr(cmd, '.'))
		return (cmd);
	i = -1;
	while (path_arr[++i])
	{
		tmp = ft_strjoin(path_arr[i], "/");
		rv = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(rv, F_OK | X_OK) == 0)
			return (rv);
		free(rv);
	}
	return (NULL);
}

static t_info	**find_abs_path(t_argument *arg)
{
	int		i;
	t_info	**info;

	info = malloc(sizeof(t_info *) * (arg->cmd_cnt + 1));
	if (!info)
		return (NULL);
	info[arg->cmd_cnt] = NULL;
	i = -1;
	while (++i < arg->cmd_cnt)
	{
		info[i] = malloc(sizeof(t_info));
		if (!info[i])
			return (NULL);
		info[i]->whole_cmd = ft_split(arg->cmd_str[i], ' ');
		info[i]->abs_path = check_file(info[i]->whole_cmd[0]);
		info[i]->executable = is_exec(info[i]->abs_path, info[i]->whole_cmd);
	}
	return (info);
}

t_info	**px_parse(t_argument *arg)
{
	const char	**path_arr = (const char **)get_path_arr(arg->envp);
	t_info		**info;
	int			i;

	if (!path_arr)
		return (find_abs_path(arg));
	info = malloc(sizeof(t_info *) * (arg->cmd_cnt + 1));
	if (!info)
		return (NULL);
	info[arg->cmd_cnt] = NULL;
	i = -1;
	while (++i < arg->cmd_cnt)
	{
		info[i] = malloc(sizeof(t_info));
		if (!info[i])
			return (NULL);
		info[i]->whole_cmd = ft_split(arg->cmd_str[i], ' ');
		info[i]->abs_path = make_abs_path(info[i]->whole_cmd[0], path_arr);
		info[i]->executable = is_exec(info[i]->abs_path, info[i]->whole_cmd);
	}
	i = -1;
	while (path_arr[++i])
		free((void *)path_arr[i]);
	free((void *)path_arr);
	return (info);
}
