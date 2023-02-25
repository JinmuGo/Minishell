/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:14 by jgo               #+#    #+#             */
/*   Updated: 2023/02/25 11:44:15 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"

t_bool print_error(const char *str)
{
    write(STDERR_FILENO, "Minishell: ", 12);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 2);
	return (FT_FALSE);
}

// bash: cd: OLDPWD not set
t_bool	print_built_in_err(char *cmd, char *key, char *msg)
{
	const char *add_colon = ft_strjoin(cmd, " : ");
	const char *line = ft_strcombine(3, add_colon, key, msg);

	set_exit_status(EXIT_FAILURE);
	return (print_error(line));
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