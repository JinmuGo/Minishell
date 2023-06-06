/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:26:12 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:53:12 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "meta_command.h"

char	*make_git_prompt(const char *cur_dir, int fd)
{
	const char	*line = get_next_line(fd);
	const char	**split_arr = (const char **)ft_split(line, '/');
	char		*rv;
	char		*branch;
	int			i;

	i = 0;
	while (split_arr[i])
		i++;
	rv = ft_strtrim(split_arr[i - 1], "\n");
	branch = ft_strjoin(" ", rv);
	free(rv);
	rv = ft_strcombine(\
		8, BOLD, CYAN, cur_dir, GRAY, branch, MAGENTA, MY_PROMPT, RESET);
	ft_free_all_arr((char **)split_arr);
	free((void *)branch);
	free((void *)line);
	return (rv);
}

char	*make_normal_prompt(const char *cur_dir)
{
	return (ft_strcombine(6, BOLD, CYAN, cur_dir, MAGENTA, MY_PROMPT, RESET));
}

char	*make_prompt(char *prev_prompt)
{
	const int	fd = open(".git/HEAD", O_RDONLY);
	const char	*cur_dir = get_cur_dir();
	char		*new_prompt;

	if (cur_dir == NULL)
		return (prev_prompt);
	if (fd != -1)
		new_prompt = make_git_prompt(cur_dir, fd);
	else
		new_prompt = make_normal_prompt(cur_dir);
	if (prev_prompt)
		free(prev_prompt);
	if (fd != -1)
		close(fd);
	return (new_prompt);
}
