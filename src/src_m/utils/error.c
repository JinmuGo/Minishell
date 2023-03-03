/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:14 by jgo               #+#    #+#             */
/*   Updated: 2023/03/03 16:03:49 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include "utils.h"
#include "meta_command.h"

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
int	parsing_error(t_err_type err)
{
	t_meta	*meta;

	if (err > 99 && err < 300)
	{
		print_error("parsing_error()");
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