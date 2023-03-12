/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:46:50 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:05:04 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "data_structure.h"
#include "meta_command.h"
#include "error.h"

int	parser(char *line, t_tree *tree)
{
	t_list	*tk_list;

	tk_list = tokenize(line);
	if (tk_list)
	{
		make_tree(tree, &tk_list, tk_list, NULL);
		edit_unlink_list();
		if (get_err_num() != ERR_NOTHING && tk_list)
			free_tk_list(&tk_list);
	}
	return (get_err_num());
}

void	edit_unlink_list(void)
{
	t_meta	*meta;
	t_list	*tmp_list;

	meta = get_meta();
	tmp_list = (meta->unlink_lst)->next;
	if (tmp_list == NULL)
		return ;
	free(meta->unlink_lst);
	meta->unlink_lst = tmp_list;
}

void	make_tree(
		t_tree *tree, t_list **tk_list, t_list *cur_list, t_tree_node *cur_node)
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
	if (dque && dque->use_size > 0)
		dque_to_tree(tree, tk_list, cur_node, dque);
	free(dque->nodes);
	free((void *)dque);
	dque = NULL;
	if (get_err_num() != ERR_NOTHING)
		return ;
	make_tree(tree, tk_list, cur_list, cur_node->right);
}

t_deque	*save_dque(t_list *tk_list, t_list **cur_list, t_deque *dque)
{
	if (get_err_num() == ERR_PIPE || get_err_num() == ERR_MULTI_PIPE)
	{
		set_err_num(ERR_PIPE);
		err_handler(get_meta());
		return (NULL);
	}
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

void	dque_to_tree(
		t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque)
{
	const t_meta	*meta = get_meta();

	if (meta->err <= ERR_MULTI_PIPE \
		&& dque->use_size > 0 \
		&& cur_node->left == NULL)
		make_left(tree, tk_list, cur_node, dque);
	if (meta->err == ERR_NOTHING \
		&& dque->use_size > 0 \
		&& cur_node->right == NULL)
		make_right(tree, tk_list, cur_node, dque);
}
