/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:17:06 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/10 09:59:14 by jgo              ###   ########.fr       */
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
	const t_meta	*meta = get_meta();

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
	const t_meta	*meta = get_meta();

	if (token->next == NULL)
	{
		if (meta->err == ERR_MULTI || meta->err == ERR_MULTI_PIPE)
			set_err_num(ERR_PIPE);
		else if (meta->err == ERR_NOTHING)
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
