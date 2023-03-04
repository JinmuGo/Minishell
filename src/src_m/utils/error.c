/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:14 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 16:13:20 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include "meta_command.h"
#include <errno.h>
#include "utils.h"

t_bool prt_err(const char *str, int exit_status)
{
    write(STDERR_FILENO, "Minishell: ", 12);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 2);
	set_exit_status(exit_status);
	return (FT_FALSE);
}

t_bool	prt_sc_err(int rv)
{
	if (rv == -1)
	{
		prt_err(strerror(errno) ,errno);
		return (FT_FALSE);
	}
	return (FT_TRUE);
}

// bash: cd: OLDPWD not set
t_bool	prt_built_in_err(char *cmd, char *key, char *msg, int exit_status)
{
	const char *add_colon = ft_strjoin(cmd, ": ");
	const char *line;

	if (key)
		line = ft_strcombine(4, add_colon, key, ": ",msg);
	else
		line = ft_strcombine(2, add_colon ,msg);
	prt_err(line, exit_status);
	ft_free_n(2, add_colon, line);
	return (FT_FALSE);
}

/**
 * @brief 
 * 
 * @return int 
 */
int	parsing_error(t_err_type err)
{
	t_meta	*meta;

	if (err > 99 && err < 300)
	{
		prt_err("parsing_error()", err);
		printf("err_num: ### %d ###\n", err);
		system("leaks minishell");
		meta = get_meta();
		meta->err = ERR_NOTHING;
		prompt();
	}
	return (128);
}

/**
 * @brief 
 * 
 * @return int 
 */

/*
int executor_error()
{
    
}

*/


/*
int heredoc_error()
{

}
*/

// int error_handler(t_err_type err)
// {
// 	if (err > 99 && err < 300)
// }

// char	*get_err_str(t_err_type err)
// {
// 	if ()
// }