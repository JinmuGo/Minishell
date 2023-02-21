/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:40:52 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/21 15:41:18 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "tree.h"
#include "deque.h"

t_tree_node	*make_pipe_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list	*token;

	if (dque->use_size > 0)
	{
		token = dque->nodes[dque->front];
		if (((t_tokenize *)(token->content))->type == PIPE)
			return (insert_pipe_node(tree, tk_list, cur_node, dque));
	}
	return (cur_node);
}

t_tree_node	*make_cmd_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list	*token;

	if (dque->use_size > 0)
	{
		token = (dque->nodes[dque->front]);
		if (((t_tokenize *)(token->content))->type == RDR || ((t_tokenize *)(token->content))->type == WORD)
			return (insert_cmd_node(tree, tk_list, cur_node, dque));
	}
	return (cur_node);
}

t_tree_node	*make_rdr_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list	*token;
	int		re_cnt;

	if (dque->use_size > 0)
	{
		re_cnt = search_rdr(dque);
		token = (t_list *)(dque->nodes[dque->front]);
		if (((t_tokenize *)(token->content))->type == RDR)
		{
			cur_node = insert_rdr_node(tree, tk_list, cur_node, dque);
			recover_dque(dque, re_cnt);
		}
	}
	return (cur_node);
}

t_tree_node	*make_s_cmd_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list	*token;

	if (dque->use_size > 0)
	{
		token = (t_list *)(dque->nodes[dque->front]);
		if (((t_tokenize *)(token->content))->type == WORD)
			return(insert_s_cmd_node(tree, tk_list, cur_node, dque));
	}
	return (cur_node);
}
