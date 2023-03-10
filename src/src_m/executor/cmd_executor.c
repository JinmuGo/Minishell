/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:30:37 by jgo               #+#    #+#             */
/*   Updated: 2023/03/10 22:46:50 by jgo              ###   ########.fr       */
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

	if (!path_arr || ft_strchr(cmd, '.') || ft_strchr(cmd, '/'))
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
	
	// dprintf(2, "s_cmd command: %s\n", simple_cmd->cmd);
	if (node == NULL || node->value == NULL)
		exit(EXIT_FAILURE);
	simple_cmd = ((t_token *)(node->value))->cmd_val.simple_cmd;
	type = is_built_in_cmd(simple_cmd->cmd);
	if (type != FT_EXTERNAL)
	{
		if (built_in(simple_cmd, type) == EXIT_SUCCESS)
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
	}
	else
	{
		if (path_arr == NULL)
		{
			prt_err(ERR_CMD_NOT_FOUND, 127);
			return ; // path 가 env에서 unset됨. command not found 
		}
		abs_path = make_abs_path(simple_cmd->cmd, path_arr);
		execve(abs_path, simple_cmd->args, (char **)envp_arr);
		prt_built_in_err(simple_cmd->cmd, NULL, ERR_CMD_NOT_FOUND, 127);
		exit(127);
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

const char **make_envp_arr(t_tree_node *node)
{
	t_simple_cmd *simple_cmd;
	int	val;

	if (node == NULL)
		return (NULL);
	simple_cmd = ((t_token *)(node->value))->cmd_val.simple_cmd;
	if (ft_strcmp(simple_cmd->cmd, "./minishell") == 0)
	{
		val = ft_atoi(get_envp_elem("SHLVL")->val);
		set_envp_elem("SHLVL", ft_itoa(val + 1));
	}
	return ((const char **)convert_char_arr());	
}

void	cmd_executor(t_tree_node *node, t_executor *execute, t_sequence sequence)
{
	const	char	**path_arr = get_path_arr();
	const	char	**envp_arr = make_envp_arr(node->right);
	t_child_proc	*child_proc;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		prt_sc_err(pid);
	signal_controller(SIG_CHILD, pid);
	if (pid == 0)
	{
		direction_handler(execute, sequence);
		rdr_executor(node->left, execute);
		s_cmd_executor(node->right, path_arr, envp_arr);
	}
	else
	{
		signal_controller(SIG_INIT);
		// post_process();
		child_proc = ft_malloc(sizeof(t_child_proc));
		child_proc->pid = pid;
		if (node->right)
			child_proc->name = (((t_token *)(node->right->value))->cmd_val.simple_cmd->cmd);
		else
			child_proc->name = NULL;
		ft_lstadd_back(&execute->child_lst, ft_lstnew(child_proc));
		ft_free_all_arr((void *)path_arr);
		if (envp_arr)
			ft_free_all_arr((void *)envp_arr);
	}
}
