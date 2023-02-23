/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:14 by jgo               #+#    #+#             */
/*   Updated: 2023/02/23 15:16:08 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error(char *str)
{
    write(2, "Minishell: ", 12);
	write(2, str, ft_strlen(str));
	write(2, "\n", 2);
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