/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:44:36 by jgo               #+#    #+#             */
/*   Updated: 2023/02/04 16:42:17 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../includes/tree.h"

void    tree_init(t_tree *tree, void *str)
{
    tree->delete_node = delete_node;
    tree->destroy = destroy;
    tree->insert = insert;
    tree->pre_order_traversal = pre_order_traversal;
    tree->root = create_node(str);
}

void	print_node(t_tree_node *node)
{
	printf("value : %s\n", node->value);
	printf("size : %d\n", node->size);
	printf("left : %d\n", node->left);
	printf("right : %d\n", node->right);
}

int main(int ac, char **av)
{
    t_tree  tree;
    
    ac++;
    tree_init(&tree, av[1]);

    tree.insert(tree.root, RIGHT, create_node(av[0]));
	tree.pre_order_traversal(tree.root, print_node);

    return (0);
}