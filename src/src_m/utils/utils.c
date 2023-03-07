/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:47:10 by jgo               #+#    #+#             */
/*   Updated: 2023/03/06 23:20:59 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "envp_command.h"
#include "meta_command.h"

char *redef_cur_dir(char *prev_dir)
{
	char	*buffer;
	char	*dst;

	if (prev_dir)
		free(prev_dir);
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
		return (NULL);
	dst = ft_strdup(buffer);
	free(buffer);
	return (dst);
}
