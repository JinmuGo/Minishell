/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:26:12 by jgo               #+#    #+#             */
/*   Updated: 2023/02/19 19:12:26 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"

char *make_git_prompt(char *cur_dir, int fd)
{
	const char *line = get_next_line(fd);
}

char	*make_normal_prompt(char *cur_dir)
{
	
}

char *make_prompt(void)
{
	const char *cur_dir = get_cur_dir();
	const int fd = open(".git/HEAD", O_RDONLY);
	char *prompt;
	
	if (fd)
		prompt = make_git_prompt(cur_dir, fd);
	else
		prompt = make_normal_prompt(cur_dir);
	close(fd);
	free((void *)cur_dir);
	return (prompt);
}