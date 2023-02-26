/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:46:42 by jgo               #+#    #+#             */
/*   Updated: 2023/02/26 15:13:15 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	px_child_process(int L, t_argument *arg, int input)
{
	const t_info	*cmd_info = arg->cmd_info[L];
	pid_t			pid;
	int				fd[2];

	if (L == arg->cmd_cnt)
		return ;
	if (L != arg->cmd_cnt - 1)
		pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		error_handling(L, arg, arg->file);
		direction_handling(L, arg, fd, input);
		execve(cmd_info->abs_path, cmd_info->whole_cmd, arg->envp);
	}
	if (L != arg->cmd_cnt - 1)
		close(fd[1]);
	px_child_process(L + 1, arg, fd[]);
	close(input);
	if (L == arg->cmd_cnt - 1)
		pid = waitpid(pid, &arg->last_status, 0);
	else
		wait(NULL);
	if (pid == -1)
		perror("fork fail");
}

void	px_parent_process(t_argument *arg, int argc, char **argv)
{
	arg->file[0] = open(argv[1], O_RDONLY, 0644);
	arg->file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	px_child_process(0, arg, arg->file[0]);
}

void	hd_parent_process(t_argument *arg, int argc, char **argv)
{
	const char	*end_flag = ft_strjoin(argv[2], "\n");
	const char	*tmp_name = find_tmp_name();
	const char	*pipe_heredoc_str = make_pipe_str(arg->cmd_cnt -1);

	arg->file[0] = open(tmp_name, O_WRONLY | O_CREAT, 0644);
	arg->file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	here_doc_prompt(end_flag, pipe_heredoc_str, arg->file[0]);
	arg->file[0] = open(tmp_name, O_RDONLY, 0644);
	if (unlink(tmp_name) == -1)
		perror("unlink error:");
	free((void *)tmp_name);
	free((void *)end_flag);
	free((void *)pipe_heredoc_str);
	px_child_process(0, arg, arg->file[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_argument	info;

	if (argc < 5)
		exit(1);
	info.cmd_cnt = argc - 3;
	info.envp = envp;
	info.cmd_str = argv + 2;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		info.cmd_info = px_parse(&info);
		px_parent_process(&info, argc, argv);
	}
	else
	{
		info.cmd_cnt--;
		info.cmd_str++;
		info.cmd_info = px_parse(&info);
		hd_parent_process(&info, argc, argv);
	}
	exit(WEXITSTATUS(info.last_status));
}
