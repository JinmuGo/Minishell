/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:46:50 by jgo               #+#    #+#             */
/*   Updated: 2023/02/22 15:22:32 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "data_structure.h"

t_tree	*parser(char *line)
{
	t_tree	*tree;
	t_list	*tk_list;

	tk_list = tokenize(line);
	tree = malloc(sizeof(t_tree));
	tree_init(tree);
	make_tree(tree, &tk_list, tk_list, NULL);
	return (tree);
}

void	make_tree(t_tree *tree, t_list **tk_list, t_list *cur_list, t_tree_node *cur_node)
{
	t_deque		*dque;

	if (!cur_list)
		return ;
	if (!tree->root)
		insert_root(tree);
	if (!cur_node && tree->root)
		cur_node = tree->root;
	if (!cur_node)
		return ;
	dque = save_dque(*tk_list, &cur_list, NULL);
	if (dque->use_size > 0)
		dque_to_tree(tree, tk_list, cur_node, dque);
	free(dque->nodes);
	dque->nodes = NULL;
	free(dque);
	dque = NULL;
	make_tree(tree, tk_list, cur_list, cur_node->right);
}

t_deque	*save_dque(t_list *tk_list, t_list **cur_list, t_deque *dque)
{
	char	*token_str;

	if (dque == NULL)
		dque = deque_init(ft_lstsize(tk_list));
	if (!(*cur_list))
		return (dque);
	if (*cur_list && ((t_tokenize *)(*cur_list)->content)->type == PIPE)
	{
		dque->push_front(dque, *cur_list);
		*cur_list = (*cur_list)->next;
		return (dque);
	}
	dque->push_rear(dque, *cur_list);
	*cur_list = (*cur_list)->next;
	save_dque(tk_list, cur_list, dque);
	return (dque);
}

void	dque_to_tree(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	if (dque->use_size > 0 && cur_node->left == NULL)
		make_left(tree, tk_list, cur_node, dque);
	if (dque->use_size > 0 && cur_node->right == NULL)
		make_right(tree, tk_list, cur_node, dque);
}
