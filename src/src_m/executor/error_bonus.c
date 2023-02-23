/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:54:05 by jgo               #+#    #+#             */
/*   Updated: 2022/12/03 15:30:44 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	file_error(const char *str)
{
	if (access(str, F_OK) == 0)
		ft_printf("Permission denied: %s\n", str);
	else
		ft_printf("No such file or directory: %s\n", str);
	exit(1);
}

void	error_handling(int L, t_argument *arg, int file[2])
{
	const t_info	*cmd_info = arg->cmd_info[L];
	const char		*first_cmd = cmd_info->abs_path;
	const char		*is_it_file = ft_strchr(cmd_info->whole_cmd[0], '/');

	if ((L != 0 && L != arg->cmd_cnt -1) && is_it_file)
		file_error(first_cmd);
	if ((L == 0 && file[0] == -1) || (L == arg->cmd_cnt -1 && file[1] == -1))
	{	
		if (file[0] == -1 && L == 0)
			file_error(*(arg->cmd_str - 1));
		if (file[1] == -1 && L == arg->cmd_cnt -1)
			file_error(*(arg->cmd_str + arg->cmd_cnt));
		exit(1);
	}
	if (!cmd_info->executable && !is_it_file)
	{
		ft_printf("command not found: %s\n", cmd_info->whole_cmd[0]);
		exit(127);
	}
}
