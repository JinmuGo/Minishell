/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:14 by jgo               #+#    #+#             */
/*   Updated: 2023/03/16 20:37:07 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include "meta_command.h"
#include <errno.h>
#include "utils.h"

t_bool	prt_err(const char *str, int exit_status)
{
	prt_sc_err(write(STDERR_FILENO, "Minishell: ", 12));
	prt_sc_err(write(STDERR_FILENO, str, ft_strlen(str)));
	prt_sc_err(write(STDERR_FILENO, "\n", 2));
	set_exit_status(exit_status);
	return (FT_FALSE);
}

t_bool	prt_sc_err(int rv)
{
	if (rv == -1)
	{
		prt_err(strerror(errno), errno);
		return (FT_FALSE);
	}
	return (FT_TRUE);
}

// bash: cd: OLDPWD not set
t_bool	prt_built_in_err(char *cmd, char *key, char *msg, int exit_status)
{
	const char	*add_colon = ft_strjoin(cmd, ": ");
	const char	*line;

	if (key)
		line = ft_strcombine(4, add_colon, key, ": ", msg);
	else
		line = ft_strcombine(2, add_colon, msg);
	prt_err(line, exit_status);
	ft_free_n(2, add_colon, line);
	return (FT_FALSE);
}

/**
 * @brief 
 * 
 * @return int 
 */
void	err_handler(t_meta *meta)
{
	const int	err = meta->err;

	if (err == ERR_NOTHING)
		return ;
	if (100 <= err && err < 200)
		parsing_error(err);
}

void	parsing_error(t_err_type err)
{
	if (err == ERR_QUOTE)
		prt_err(ERR_SYN_QUOTE, 258);
	if (err == ERR_MULTI)
		prt_err(ERR_SYN_ML, 258);
	if (err == ERR_PIPE)
		prt_err(ERR_SYN_PIPE, 258);
	if (err == ERR_MULTI_PIPE)
		prt_err(ERR_SYN_PIPE, 258);
	if (err == ERR_FIRST_PIPE)
		prt_err(ERR_SYN_PIPE, 258);
	if (err == ERR_RDR_IN)
		prt_err(ERR_SYN_RDR_IN, 258);
	if (err == ERR_RDR_OUT)
		prt_err(ERR_SYN_RDR_OUT, 258);
	if (err == ERR_RDR_HERE)
		prt_err(ERR_SYN_RDR_HERE, 258);
	if (err == ERR_RDR_APPEND)
		prt_err(ERR_SYN_RDR_APPEND, 258);
	if (err == ERR_NL)
		prt_err(ERR_SYN_RDR_NL, 258);
}
