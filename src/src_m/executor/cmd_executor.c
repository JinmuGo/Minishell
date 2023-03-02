/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:30:37 by jgo               #+#    #+#             */
/*   Updated: 2023/03/02 09:50:37 by jgo              ###   ########.fr       */
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
#include "envp_command.h"

static const char	**get_path_arr(void)
{
	const char *path = get_envp_elem("PATH")->val;

	if (path)
		return ((const char **)ft_split(path, ':'));
	else
		return (NULL);
}

char	*make_abs_path(char *cmd, const char **path_arr)
{
	char	*rv;
	char	*tmp;
	int		i;

	if (!path_arr)
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

void	s_cmd_executor(t_simple_cmd *simple_cmd, const char **path_arr,const char **envp_arr)
{
	char	*abs_path;
	t_simple_cmd_type type;
	
	if (simple_cmd == NULL)
		return ;
	type = is_built_in_cmd(simple_cmd->cmd);
	if (type != FT_EXTERNAL)
		built_in(simple_cmd, type);
	else
	{
		if (path_arr == NULL)
		{
			print_error(ERR_CMD_NOT_FOUND, 127);
			return ; // path 가 env에서 unset됨. command not found 
		}
		abs_path = make_abs_path(simple_cmd->cmd, path_arr);
		print_system_call_err(execve(abs_path, simple_cmd->args, (char **)envp_arr));
	}
}

void	cmd_executor(t_tree_node *node, t_executor *execute)
{
	const	char	**path_arr = get_path_arr();
	const	char	**envp_arr = (const char **)convert_char_arr();
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_system_call_err(pid);
	signal_controller(SIG_CHILD, pid);
	if (pid == 0)
	{
		// child
		rdr_executor(node->left, execute);
		s_cmd_executor(node->right->value, path_arr, envp_arr);
	}
	else
	{
		// parent
		// wait_pid
		waitpid(pid, get_exit_status(), 0);
		signal_controller(SIG_INIT);
		ft_free_all_arr((void *)path_arr);
		ft_free_all_arr((void *)envp_arr);
	}
}