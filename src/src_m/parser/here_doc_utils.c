/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:22:55 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/10 18:03:55 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "data_structure.h"
#include "meta_command.h"
#include "expander.h"
#include "signal_controller.h"
#include "error.h"

char	*creat_file(void)
{
	char	*file_path;
	char	*num_str;
	int		num;

	num = 0;
	num_str = ft_itoa(num);
	file_path = ft_strjoin("/tmp/minishell_tmp", num_str);
	while (file_path)
	{	
		if (access(file_path, F_OK) != 0)
			break ;
		free(num_str);
		free(file_path);
		num_str = ft_itoa(num++);
		file_path = ft_strjoin("/tmp/minishell_tmp", num_str);
	}
	free(num_str);
	return (file_path);
}

t_bool	check_heredoc_quote(char *str)
{
	int	idx;

	idx = 0;
	while (str && str[idx])
	{
		if (str[idx] == S_QUOTE || str[idx] == D_QUOTE)
			return (FT_TRUE);
		idx++;
	}
	return (FT_FALSE);
}
