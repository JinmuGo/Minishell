/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:30:37 by jgo               #+#    #+#             */
/*   Updated: 2023/03/03 22:31:39 by jgo              ###   ########.fr       */
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

void	s_cmd_executor(t_tree_node *node, const char **path_arr,const char **envp_arr)
{
	char	*abs_path;
	t_simple_cmd_type type;
	t_simple_cmd *simple_cmd;
	
	simple_cmd = ((t_token *)(node->value))->cmd_val.simple_cmd;
	// dprintf(2, "s_cmd command: %s\n", simple_cmd->cmd);
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
		execve(abs_path, simple_cmd->args, (char **)envp_arr);
		exit(EXIT_FAILURE);
	}
}

void	direction_handler(t_executor *execute, t_sequence sequence)
{
	if (sequence == FIRST)
	{
		dup2(execute->cur_fd[WRITE], STDOUT_FILENO);
		close(execute->cur_fd[READ]);
	}
	else if (sequence == MIDDLE)
	{
		dup2(execute->prev_fd[READ], STDIN_FILENO);
		dup2(execute->cur_fd[WRITE], STDOUT_FILENO);
		close(execute->cur_fd[READ]);
	}
	else
	{
		dup2(execute->cur_fd[READ], STDIN_FILENO);
		close(execute->cur_fd[WRITE]);
	}
}

void	cmd_executor(t_tree_node *node, t_executor *execute, t_sequence sequence)
{
	const	char	**path_arr = get_path_arr();
	const	char	**envp_arr = (const char **)convert_char_arr();
	pid_t	*pid_cpy;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_system_call_err(pid);
	signal_controller(SIG_CHILD, pid);
	if (pid == 0)
	{
		// pipe

		direction_handler(execute, sequence);
		rdr_executor(node->left, execute);
		// dprintf(2, "pid: %d cur fd: %d %d\n", pid,execute->cur_fd[0], execute->cur_fd[1]);
		// dprintf(2, "pid: %d prev fd: %d %d\n", pid,execute->prev_fd[0], execute->prev_fd[1]);
		s_cmd_executor(node->right, path_arr, envp_arr);
	}
	else
	{
		// dprintf(2, "pid:%d type: %d edge: %d\n", pid, ((t_token *)(node->value))->type, edge);
		signal_controller(SIG_INIT);
		pid_cpy = ft_malloc(sizeof(pid_t));
		*pid_cpy = pid;
		ft_lstadd_back(&execute->pid_lst, ft_lstnew(pid_cpy));
		ft_free_all_arr((void *)path_arr);
		ft_free_all_arr((void *)envp_arr);
	}
}