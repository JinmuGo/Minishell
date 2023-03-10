/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:20:14 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/10 15:59:15 by sanghwal         ###   ########seoul.kr  */
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

void	write_to_file(t_list **tk_list, t_deque *dque, int fd)
{
	t_tokenize	*token;
	char		*delimter;
	char		*new_delimter;

	token = ((t_list *)(dque->pop_front(dque)))->content;
	delimter = token->str;
	new_delimter = NULL;
	if (validation_delimter(delimter, &new_delimter))
		normal_write(fd, new_delimter);
	else
		expand_write(fd, new_delimter);
	free(new_delimter);
	delete_lst_node(tk_list, token);
}

void	normal_write(int fd, char *delimter)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if ((ft_strncmp(line, delimter, ft_strlen(line)) == 0 && \
			ft_strlen(line) == ft_strlen(delimter)))
		{
			free(line);
			break ;
		}
		normal_write_util(fd, line);
	}
}

void	expand_write(int fd, char *delimter)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if ((ft_strncmp(line, delimter, ft_strlen(line)) == 0 && \
			ft_strlen(line) == ft_strlen(delimter)))
		{
			free(line);
			break ;
		}
		expand_write_util(fd, line);
	}
}

void	normal_write_util(int fd, char *line)
{
	char	*tmp;

	if (!line)
		prt_sc_err(write(fd, "\n", 1));
	else
	{
		tmp = ft_strjoin(line, "\n");
		prt_sc_err(write(fd, tmp, ft_strlen(line) + 1));
		free(tmp);
		free(line);
	}
}

void	expand_write_util(int fd, char *line)
{
	char	*tmp;

	if (!line)
		prt_sc_err(write(fd, "\n", 1) == -1);
	else
	{
		line = shell_param_expand(line);
		tmp = ft_strjoin(line, "\n");
		prt_sc_err(write(fd, tmp, ft_strlen(line) + 1));
		free(tmp);
		free(line);
	}
}
