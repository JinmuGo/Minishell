/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:56:53 by jgo               #+#    #+#             */
/*   Updated: 2023/02/07 17:58:53 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

t_tree_node *create_node(void *value)
{
	t_tree_node *node;

	node = ft_malloc(sizeof(t_tree_node));
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void    insert(t_tree_node *node, t_tree_edge edge, t_tree_node *child)
{
	if (edge == LEFT)
		node->left = child;
	if (edge == RIGHT)
		node->right = child;
};

void    pre_order_traversal(t_tree_node *node, void(*f)(t_tree_node*))
{
	if (node == NULL)
		return ;
	f(node);
	pre_order_traversal(node->left, f);
	pre_order_traversal(node->right, f);
};

void	delete_node(t_tree_node *node)
{
	free(node->value);
	free(node);
};

void	destroy(t_tree *tree)
{
	pre_order_traversal(tree->root, delete_node);
};