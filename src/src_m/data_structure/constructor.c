/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:08:05 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/06 21:10:23 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "tree.h"

void	tree_init(t_tree *tree)
{
	tree->root = NULL;
	tree->delete_node = delete_node;
	tree->destroy = destroy;
	tree->insert = insert;
	tree->pre_order_traversal = pre_order_traversal;
}