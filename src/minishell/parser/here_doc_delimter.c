/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_delimter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:21:42 by sanghwal          #+#    #+#             */
/*   Updated: 2023/05/14 08:54:16 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "data_structure.h"
#include "meta_command.h"

char	*edit_delimter(char *delimter)
{
	int		size;

	size = get_new_delimter_size(delimter);
	return (make_new_delimter(delimter, size));
}

bool	validation_delimter(char *delimter, char **new_delimter)
{
	bool	quote;

	quote = check_heredoc_quote(delimter);
	*new_delimter = edit_delimter(delimter);
	return (quote);
}

int	get_new_delimter_size(char *delimter)
{
	int		size;
	int		idx;
	t_stack	quote;

	idx = 0;
	size = 0;
	stack_init(&quote);
	while (delimter && delimter[idx])
	{
		if (quote.size > 0 && delimter[idx] == *(char *)quote.peek(&quote))
		{
			quote.pop(&quote);
			idx++;
		}
		else if (quote.size == 0 \
			&& (delimter[idx] == '\'' || delimter[idx] == '\"'))
			quote.push(&quote, &delimter[idx++]);
		else
		{
			idx++;
			size++;
		}
	}
	stack_destory(&quote);
	return (size);
}

char	*make_new_delimter(char *delimter, int size)
{
	t_stack	quote;
	int		idx;
	int		new_idx;
	char	*new_delimter;

	stack_init(&quote);
	new_delimter = ft_calloc(1, size + 1);
	idx = 0;
	new_idx = 0;
	while (delimter && delimter[idx])
	{
		if (quote.size > 0 && delimter[idx] == *(char *)quote.peek(&quote))
		{
			quote.pop(&quote);
			idx++;
		}
		else if (quote.size == 0 \
			&& (delimter[idx] == '\'' || delimter[idx] == '\"'))
			quote.push(&quote, &delimter[idx++]);
		else
			new_delimter[new_idx++] = delimter[idx++];
	}
	return (new_delimter);
}
