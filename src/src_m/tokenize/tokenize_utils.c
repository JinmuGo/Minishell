/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:14:27 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/20 20:54:23 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "stack.h"
#include "parser.h"
#include "utils.h"

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

void	print_tokenize(t_list *tk_list)
{
	char		*type;
	int			cnt;
	t_tokenize	*token;
	t_list		*tmp = tk_list;

	printf("\n-----token_info-----\n");
	cnt = 1;
	while (tmp)
	{
		token = tmp->content;
		if (token->type == 0)
			type = "RDR";
		if (token->type == 1)
			type = "PIPE";
		if (token->type == 2)
			type = "CMD";
		if (token->type == 3)
			type = "WORD";
		printf("--token_%d--\ntoken_str : %s\ntoken_type: %s\ntoken_size : %d\n\n", \
			cnt, token->str, type, token->size);
		tmp = tmp->next;
		cnt++;
	}
	return ;
}
