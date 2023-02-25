/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:33 by jgo               #+#    #+#             */
/*   Updated: 2023/02/25 20:49:49 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* printf, perror*/
# include <stdio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* readline, rl_clear_history, rl_on_new_line, rl_replace_line,
	rl_redisplay, add_history */
# include <readline/readline.h>
# include <readline/history.h>
void rl_replace_line (const char *text, int clear_undo);

/* write, read, close, access, pipe, dup, dup2, execve, fork, getcwd, chdir */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>

/* stat, lstat, fstat */
# include <sys/stat.h>

/* open, unlink */
# include <fcntl.h>

/* strerror */
# include <string.h>

/* signal, sigaction, sigemptyset, sigaddset */
# include <signal.h>

/* tcsetattr, tcgetattr */
# include <termios.h>

/* tgetent, tgetflag, tgetnum, tgetstr */
# include <curses.h>
# include <term.h>

/* libft */
# include "libft.h"

#endif