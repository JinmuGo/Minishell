/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:40:52 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/09 20:24:14 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "data_structure.h"
#include "meta_command.h"

t_tree_node	*make_pipe_node(
	t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list	*token;

	if (dque->use_size > 0)
	{
		token = dque->nodes[dque->front];
		if (((t_tokenize *)(token->content))->type == PIPE)
		{
			lexer_pipe(token, tk_list);
			if (get_err_num() == ERR_FIRST_PIPE)
				return (NULL);
			return (insert_pipe_node(tree, tk_list, cur_node, dque));
		}
	}
	return (cur_node);
}

t_tree_node	*make_cmd_node(
	t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list	*token;

	if (dque->use_size > 0)
	{
		token = (dque->nodes[dque->front]);
		if (((t_tokenize *)(token->content))->type == RDR \
			|| ((t_tokenize *)(token->content))->type == WORD)
			return (insert_cmd_node(tree, tk_list, cur_node, dque));
	}
	return (cur_node);
}

t_tree_node	*make_rdr_node(
	t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list			*token;
	int				re_cnt;
	const t_meta	*meta = get_meta();

	if (dque->use_size > 0)
	{
		re_cnt = search_rdr(dque);
		token = (t_list *)(dque->nodes[dque->front]);
		if (((t_tokenize *)(token->content))->type == RDR)
		{
			lexer_rdr(token);
			if (re_cnt > 0 && dque->use_size == 2)
				set_err_num(ERR_PIPE);
			else if (meta->err == ERR_NOTHING || validation_heredoc(token))
			{
				cur_node = insert_rdr_node(tree, tk_list, cur_node, dque);
				recover_dque(dque, re_cnt);
			}
			if (meta->err != ERR_NOTHING)
			{
				while (dque->use_size > 0)
					dque->pop_front(dque);
				return (NULL);
			}
		}
	}
	return (cur_node);
}

t_tree_node	*make_s_cmd_node(
	t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list	*token;

	if (dque->use_size > 0)
	{
		token = (t_list *)(dque->nodes[dque->front]);
		if (((t_tokenize *)(token->content))->type == WORD)
			return (insert_s_cmd_node(tree, tk_list, cur_node, dque));
	}
	return (cur_node);
}
