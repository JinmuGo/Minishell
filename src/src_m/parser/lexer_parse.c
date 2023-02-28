/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:17:06 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/28 22:18:54 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "data_structure.h"
#include "meta_command.h"
#include "error.h"

void	lexer_pipe(t_list *token, t_list **tk_list)
{
	t_meta *meta = get_meta();

	if (((t_tokenize *)(*tk_list)->content)->type == PIPE)
		meta->err = ERR_FIRST_PIPE;
	else if (((t_tokenize *)(token->content))->size > 1)
		meta->err = ERR_MULTI_PIPE;
	else if (token->next == NULL)
		meta->err = ERR_MULTI;
	else if (((t_tokenize *)(token->next->content))->type == PIPE)
		meta->err = ERR_PIPE;
	return ;
}

int	lexer_rdr(t_list *token)
{
	t_meta *meta = get_meta();

	if (((t_tokenize *)(token->content))->size > 3)
		meta->err = ERR_RDR_MULTI;
	else if (token->next == NULL)
	{
		if (meta->err == ERR_MULTI || meta->err == ERR_MULTI_PIPE)
			meta->err = ERR_PIPE;
		else if (meta->err == ERR_NOTHING)
			meta->err = ERR_NL;
	}
	else if (((t_tokenize *)(token->next->content))->type == RDR)
	{
		if (!ft_strncmp(((t_tokenize *)(token->next->content))->str, "<", 2))
			meta->err = ERR_RDR_IN;
		else if (!ft_strncmp(((t_tokenize *)(token->next->content))->str, ">", 2))
			meta->err = ERR_RDR_OUT;
		else if (((t_tokenize *)(token->next->content))->str[0] == '<')
			meta->err = ERR_RDR_HERE;
		else if (((t_tokenize *)(token->next->content))->str[0] == '>')
			meta->err = ERR_RDR_APPEND;
	}
	return (meta->err);
}
