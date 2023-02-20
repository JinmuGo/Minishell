/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:54:20 by jgo               #+#    #+#             */
/*   Updated: 2022/12/13 14:37:41 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	direction_handling(int L, t_argument *arg, int fd[2], int input)
{
	if (L != arg->cmd_cnt - 1)
		close(fd[0]);
	if (L == 0)
		dup2(arg->file[0], STDIN_FILENO);
	else
		dup2(input, STDIN_FILENO);
	if (L != arg->cmd_cnt - 1)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(arg->file[1], STDOUT_FILENO);
}

char	*check_file(char *str)
{
	if (!ft_strchr(str, '/'))
		return (NULL);
	return (str);
}
