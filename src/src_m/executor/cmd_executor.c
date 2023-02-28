/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:30:37 by jgo               #+#    #+#             */
/*   Updated: 2023/02/28 17:29:25 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "executor.h"
#include "built_in.h"
#include "error.h"
#include "signal_controller.h"
#include "meta_command.h"
#include "data_structure.h"

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

void	s_cmd_executor(t_simple_cmd *simple_cmd)
{
	const t_simple_cmd_type type = is_built_in_cmd(simple_cmd->cmd);
	char	*abs_path;

	if (type != FT_EXTERNAL)
		built_in(simple_cmd, type);
	abs_path = get_	
}

void	cmd_executor(t_tree_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_system_call_err(pid);
	signal_controller(SIG_CHILD, pid);
	if (pid == 0)
	{
		// child
		rdr_executor(node->left);
		s_cmd_executor(node->right->value);
	}
	else
	{
		// parent
		// wait_pid
		waitpid(pid, get_exit_status(), 0);
		
	}
}