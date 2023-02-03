/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:52:37 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/03 17:53:13 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "stack.h"
#include "parser.h"
#include "utils.h"

t_list	*tokenize(char *line)
{
	t_list	*tk_list;
	char	*tmp;

	tk_list = ft_malloc(sizeof(t_list));
	make_tk_list(tk_list, line, 0);
	print_tokenize(tk_list->next);
	return (tk_list);
}

void	make_tk_list(t_list *tk_list, char *line, int size)
{
	t_stack	quote;
	// list만들기 재귀
	stack_init(&quote);
	if (line[size] == '\0')
		return ;
	while ((9 <= line[size] && line[size] <= 13) || line[size] == 32)
		size++;
	size += make_word(tk_list, &line[size], 0, &quote);
	if (quote.arr)
	{
		perror("unclosed quote");
		free(line);
		prompt();
	}
	// 파이프 처리 (line++)
	// 리다이렉션 처리 (rdr_type 구분해서 저장) (line++)
	// list만들기 재귀 (tk_list, (&line + size))
	make_tk_list(tk_list, line, size);
}

int	make_word(t_list *tk_list, char *line, t_tokenize *token, t_stack *qte)
{
	if (!token)
		token = tokenize_init(token, WORD);
	if (line[token->size] == D_QUOTE || line[token->size] == S_QUOTE)
		in_quote(line, token, qte);
	if (line[token->size] == '|' || line[token->size] == '<' || \
		line[token->size] == '>' || (9 <= line[token->size] && \
		line[token->size] <= 13) || line[token->size] == 32 || \
		line[token->size] == '\0')
		return(token_node_add(tk_list, line, token));
	token->size++;
	make_word(tk_list, line, token, qte);
	return(token->size);
}

void	in_quote(char *line, t_tokenize *token, t_stack *qte)
{
	if (qte->size == 0)
		qte->push(qte, &line[token->size]);
	else if (line[token->size] == *(char *)qte->peek(qte))
		qte->pop(qte);
	// printf("line: %c, qte: %c\n", line[token->size], *(char *)qte->peek(qte));
}

int	token_node_add(t_list *tk_list, char *line, t_tokenize *token)
{
	// t_list	*new;
	token->str = ft_malloc(sizeof(char) * (token->size + 1));
	ft_strlcpy(token->str, line, token->size + 1);
	// new = ft_lstnew(token);
	ft_lstadd_back(&tk_list, ft_lstnew(token));
	return (token->size);
}

t_tokenize	*tokenize_init(t_tokenize *token, t_token_type type)
{
	if (!token)
		token = ft_malloc(sizeof(t_tokenize));
	token->type = type;
	token->size =0;
	return (token);
}


void	print_tokenize(t_list *tk_list)
{
	char	*type;
	t_tokenize	*token;
	t_list	*tmp = tk_list;
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
		printf("-token_info-\ntoken_str : %s\ntoken_type: %s\ntoken_size : %d\n\n", \
			token->str, type, token->size);
		tmp = tmp->next;
	}
	return ;
}
