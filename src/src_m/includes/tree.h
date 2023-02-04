/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:48:10 by jgo               #+#    #+#             */
/*   Updated: 2023/02/04 16:27:02 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

t_tree_node *create_node(void *value);
void		insert(t_tree_node *node, t_tree_edge edge, t_tree_node *child);
void		pre_order_traversal(t_tree_node *node, void(*f)(t_tree_node*));
void		delete_node(t_tree_node *node);
void		destroy(t_tree *tree);

#endif