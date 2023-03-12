/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:36 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/12 17:00:21 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "data_structure.h"

void	insert_root(t_tree *tree)
{
	t_tree_node	*root;
	t_token		*value;

	value = ft_malloc(sizeof(t_token));
	value->cmd_val.pipe = ft_malloc(sizeof(t_pipe));
	value->type = PIPE;
	value->cmd_val.pipe->fd[0] = 0;
	value->cmd_val.pipe->fd[1] = 0;
	root = create_node(value);
	tree->root = root;
}

t_tree_node	*insert_pipe_node(
	t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_token		*value;
	t_tokenize	*token;
	t_tree_node	*new_node;

	token = ((t_list *)(dque->pop_front(dque)))->content;
	value = make_value(tk_list, token, dque);
	new_node = create_node(value);
	insert(cur_node, RIGHT, new_node);
	return (new_node);
}

t_tree_node	*insert_cmd_node(
	t_tree *tree, t_tree_node *cur_node)
{
	t_token		*value;
	t_tree_node	*new_node;

	value = ft_malloc(sizeof(t_token));
	value->type = CMD;
	new_node = create_node(value);
	if (cur_node->left == NULL && cur_node != tree->root)
		insert(cur_node, LEFT, new_node);
	else
		insert(cur_node, RIGHT, new_node);
	return (new_node);
}

t_tree_node	*insert_rdr_node(
	t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_token		*value;
	t_tokenize	*token;
	t_tree_node	*new_node;

	token = ((t_list *)(dque->pop_front(dque)))->content;
	value = make_value(tk_list, token, dque);
	new_node = create_node(value);
	insert(cur_node, LEFT, new_node);
	return (new_node);
}

t_tree_node	*insert_s_cmd_node(
	t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_token		*value;
	t_tokenize	*token;
	t_tree_node	*new_node;

	token = ((t_list *)(dque->pop_front(dque)))->content;
	value = make_value(tk_list, token, dque);
	new_node = create_node(value);
	insert(cur_node, RIGHT, new_node);
	return (new_node);
}
