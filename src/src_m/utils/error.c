/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:14 by jgo               #+#    #+#             */
/*   Updated: 2023/02/26 15:22:25 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include <errno.h>

t_bool print_error(const char *str, int exit_status)
{
    write(STDERR_FILENO, "Minishell: ", 12);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 2);
	set_exit_status(exit_status);
	return (FT_FALSE);
}

void	print_system_call_err(int rv)
{
	if (rv == -1)
		print_error(strerror(errno) ,errno);
}

// bash: cd: OLDPWD not set
t_bool	print_built_in_err(char *cmd, char *key, char *msg)
{
	const char *add_colon = ft_strjoin(cmd, ": ");
	const char *line = ft_strcombine(4, add_colon, key, ": ",msg);

	print_error(line, EXIT_FAILURE);
	ft_free_n(2, add_colon, line);
	return (FT_FALSE);
}

/**
 * @brief 
 * 
 * @return int 
 */

/*
int parsing_error()
{
    
}
*/

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

/*
int error_handler(t_err_type err)
{
    
}
*/