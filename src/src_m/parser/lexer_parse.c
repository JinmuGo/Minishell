/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:17:06 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/12 17:01:46 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "meta_command.h"

void	lexer_pipe(t_list *token, t_list **tk_list)
{
	if (((t_tokenize *)(*tk_list)->content)->type == PIPE)
		set_err_num(ERR_FIRST_PIPE);
	else if (((t_tokenize *)(token->content))->size > 1)
		set_err_num(ERR_MULTI_PIPE);
	else if (token->next == NULL)
		set_err_num(ERR_MULTI);
	else if (((t_tokenize *)(token->next->content))->type == PIPE)
		set_err_num(ERR_PIPE);
	return ;
}

void	lexer_rdr(t_list *token)
{
	if (token->next == NULL)
	{
		if (get_err_num() == ERR_MULTI || get_err_num() == ERR_MULTI_PIPE)
			set_err_num(ERR_PIPE);
		else if (get_err_num() == ERR_NOTHING)
			set_err_num(ERR_NL);
	}
	else if (((t_tokenize *)(token->next->content))->type == RDR)
	{
		if (!ft_strncmp(
				((t_tokenize *)(token->next->content))->str, "<", 2))
			set_err_num(ERR_RDR_IN);
		else if (!ft_strncmp(
				((t_tokenize *)(token->next->content))->str, ">", 2))
			set_err_num(ERR_RDR_OUT);
		else if (((t_tokenize *)(token->next->content))->str[0] == '<')
			set_err_num(ERR_RDR_HERE);
		else if (((t_tokenize *)(token->next->content))->str[0] == '>')
			set_err_num(ERR_RDR_APPEND);
	}
}
