/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:46:42 by jgo               #+#    #+#             */
/*   Updated: 2022/12/03 17:23:19 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int L, t_argument *arg, int input)
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
	child_process(L + 1, arg, fd[0]);
	close(input);
	if (L == arg->cmd_cnt - 1)
		pid = waitpid(pid, &arg->last_status, 0);
	else
		wait(NULL);
	if (pid == -1)
		perror("fork fail");
}

void	parent_process(t_argument *arg, int argc, char **argv)
{
	arg->file[0] = open(argv[1], O_RDONLY, 0644);
	arg->file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	child_process(0, arg, arg->file[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_argument	info;

	if (argc < 5)
	{
		ft_printf("you need at least five argument\n");
		exit(1);
	}
	info.cmd_cnt = argc - 3;
	info.envp = envp;
	info.cmd_str = argv + 2;
	info.cmd_info = px_parse(&info);
	parent_process(&info, argc, argv);
	exit(WEXITSTATUS(info.last_status));
}
