/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:15 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:58:04 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"
#include "meta_command.h"
#include "error.h"
#include <errno.h>

t_bool	exec_cd(char *cur_path)
{
	t_hash_elem	*elem;
	char		*path;

	path = NULL;
	if (cur_path == NULL || ft_strcmp(cur_path, "~") == 0)
	{
		elem = get_envp_elem("HOME");
		if (path == NULL && elem == NULL)
			return (prt_built_in_err("cd", "HOME", ERR_NOT_SET, EXIT_FAILURE));
		path = elem->val;
	}
	else if (ft_strncmp(cur_path, "-", ft_strlen(cur_path)) == 0)
	{
		elem = get_envp_elem("OLDPWD");
		if (elem == NULL)
			return (\
				prt_built_in_err("cd", "OLDPWD", ERR_NOT_SET, EXIT_FAILURE));
		path = elem->val;
	}
	else
		path = cur_path;
	if (chdir(path) == -1)
		return (prt_built_in_err(path, NULL, strerror(errno), errno));
	return (FT_TRUE);
}

int	ft_cd(t_simple_cmd *simple_cmd)
{
	t_hash_elem	*pwd;
	char		*cwd;

	if (exec_cd(simple_cmd->args[1]) == BUILT_IN_EXEC_OK)
	{
		pwd = get_envp_elem("PWD");
		if (pwd)
			set_envp_elem(ft_strdup("OLDPWD"), ft_strdup(pwd->val));
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
		{
			prt_err(strerror(errno), errno);
			return (EXIT_FAILURE);
		}
		set_envp_elem(ft_strdup("PWD"), cwd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
