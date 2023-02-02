/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:52:37 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/02 17:18:23 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "stack.h"
#include "parser.h"
#include "util.h"

t_list	*tokenize(char *line)
{
	t_list	*tk_list;
	char	*tmp;

	tk_list = ft_malloc(sizeof(t_list));
	tmp = ft_strdup(line);
	make_tk_list(tk_list,tmp);
	free(tmp);
	print_tokenize(tk_list->next->content);
	return (tk_list);
}

void	make_tk_list(t_list *tk_list, char *line)
{
	// list만들기 재귀
	// 문자열 종료시 탈출
	if (*line == '\0')
		return ;
	// 공백 넘어가기 (line++)
	while ((9 <= *line && *line <= 13) || *line == 32)
		line++;
	// WORD 처리 (|, <, >, <<, >>, 공백) 만날때까지
	make_word(tk_list, line, 0);
	// 파이프 처리 (line++)
	// 리다이렉션 처리 (rdr_type 구분해서 저장) (line++)
	// list만들기 재귀 (tk_list, (&line + size))
}

void	make_word(t_list *tk_list, char *line, t_tokenize *token)
{	
	if (!token)
		token = tokenize_init(token, WORD);
	if (line[token->size] == '|' || line[token->size] == '<' || \
		line[token->size] == '>' || (9 <= line[token->size] && \
		line[token->size] <= 13) || line[token->size] == 32)
		return(token_node_add(tk_list, line, token));
	// if (line[token->size] == '\"' || line[token->size] == '\'')
		// in_quote(line, token);
	else
		token->size++;
	make_word(tk_list, line, token);
}

void	token_node_add(t_list *tk_list, char *line, t_tokenize *token)
{
	// t_list	*new;
	token->str = ft_malloc(sizeof(char) * (token->size + 1));
	ft_strlcpy(token->str, line, token->size + 1);
	// new = ft_lstnew(token);
	ft_lstadd_back(&tk_list, ft_lstnew(token));
}

t_tokenize	*tokenize_init(t_tokenize *token, t_token_type type)
{
	token = ft_malloc(sizeof(t_tokenize));
	token->type = type;
	token->size =0;
	return (token);
}


void	print_tokenize(t_tokenize *token)
{
	char	*type;
	if (token)
	{
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
	}
	return ;
}
