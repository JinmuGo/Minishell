/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:14:27 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/17 17:05:49 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "data_structure.h"
#include "parser.h"

void	in_quote(char *line, t_tokenize *token, t_stack *qte)
{
	if (qte->size == 0)
		qte->push(qte, &line[token->size]);
	else if (line[token->size] == *(char *)qte->peek(qte))
		qte->pop(qte);
}

int	token_node_add(t_list **tk_list, char *line, t_tokenize *token)
{
	if (token->size == 0)
	{
		free(token);
		return (0);
	}
	token->str = ft_malloc(sizeof(char) * (token->size + 1));
	ft_strlcpy(token->str, line, token->size + 1);
	ft_lstadd_back(tk_list, ft_lstnew(token));
	return (token->size);
}

t_tokenize	*tokenize_init(t_tokenize *token, t_token_type type)
{
	if (!token)
		token = ft_malloc(sizeof(t_tokenize));
	token->type = type;
	token->size = 0;
	return (token);
}

void	free_tk_list(t_list **tk_list)
{
	t_list	*tmp;

	if (!*tk_list)
		return ;
	while (*tk_list)
	{
		tmp = (*tk_list)->next;
		free_token_str((*tk_list)->content);
		free(*tk_list);
		*tk_list = tmp;
	}
}

void	free_token_str(t_tokenize *content)
{
	if (content)
	{
		if (content->str)
		{
			free(content->str);
			content->str = NULL;
		}
		free(content);
		content = NULL;
	}
}
