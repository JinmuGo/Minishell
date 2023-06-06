/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:52:37 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/13 13:50:32 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "data_structure.h"
#include "parser.h"
#include "utils.h"
#include "meta_command.h"

t_list	*tokenize(char *line)
{
	t_list	*tk_list;
	t_list	*tmp;

	tk_list = ft_calloc(sizeof(t_list), 1);
	make_tk_list(&tk_list, line, 0);
	if (tk_list)
	{
		tmp = tk_list->next;
		free(tk_list);
		tk_list = tmp;
	}
	else
		set_err_num(ERR_QUOTE);
	return (tk_list);
}

void	make_tk_list(t_list **tk_list, char *line, int size)
{
	t_stack	quote;

	stack_init(&quote);
	if (line[size] == '\0')
		return ;
	while ((9 <= line[size] && line[size] <= 13) || line[size] == 32)
		size++;
	size += treat_word(tk_list, &line[size], 0, &quote);
	if (quote.arr)
	{
		stack_destory(&quote);
		free_tk_list(tk_list);
		tk_list = NULL;
		return ;
	}
	size += treat_pipe(tk_list, &line[size], 0);
	size += treat_rdr(tk_list, &line[size], 0);
	make_tk_list(tk_list, line, size);
}

int	treat_word(t_list **tk_list, char *line, t_tokenize *token, t_stack *qte)
{
	if (!token)
		token = tokenize_init(token, WORD);
	if (line[token->size] == D_QUOTE || line[token->size] == S_QUOTE)
		in_quote(line, token, qte);
	if ((qte->size == 0 && (line[token->size] == '|' || \
		line[token->size] == '<' || \
		line[token->size] == '>' || ft_isspace(line[token->size]))) || \
		line[token->size] == '\0')
		return (token_node_add(tk_list, line, token));
	token->size++;
	treat_word(tk_list, line, token, qte);
	return (token->size);
}

int	treat_pipe(t_list **tk_list, char *line, t_tokenize *token)
{
	if (!token)
		token = tokenize_init(token, PIPE);
	if (line[token->size] != '|')
		return (token_node_add(tk_list, line, token));
	token->size++;
	treat_pipe(tk_list, line, token);
	return (token->size);
}

int	treat_rdr(t_list **tk_list, char *line, t_tokenize *token)
{
	if (!token)
		token = tokenize_init(token, RDR);
	if (token->size > 0)
	{
		if (line[token->size - 1] != line[token->size])
			return (token_node_add(tk_list, line, token));
		if (token->size == 2)
			return (token_node_add(tk_list, line, token));
	}
	if (line[token->size] == '<' || line[token->size] == '>')
		token->size++;
	else
		return (token_node_add(tk_list, line, token));
	treat_rdr(tk_list, line, token);
	return (token->size);
}
