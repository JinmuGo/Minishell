/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:46:05 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/17 17:05:59 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "data_structure.h"

t_list	*delete_lst_node(t_list **tk_list, t_tokenize *token)
{
	t_list	*del_node;
	t_list	*pre_node;

	if ((*tk_list)->content == token)
	{
		del_node = *tk_list;
		*tk_list = (*tk_list)->next;
		free_token_str(del_node->content);
		free(del_node);
		del_node = NULL;
	}
	else
	{
		pre_node = *tk_list;
		while (pre_node->next->content != token)
			pre_node = pre_node->next;
		del_node = pre_node->next;
		pre_node->next = del_node->next;
		free_token_str(del_node->content);
		free(del_node);
		del_node = NULL;
	}
	return (*tk_list);
}

int	search_rdr(t_deque *dque)
{
	t_list	*token;
	int		cnt;
	int		re_cnt;

	cnt = dque->use_size;
	re_cnt = 0;
	while (cnt > 0)
	{
		if (((t_tokenize *)(((t_list *)
					(dque->nodes[dque->front]))->content))->type == RDR)
			return (re_cnt);
		token = dque->pop_front(dque);
		dque->push_rear(dque, token);
		cnt--;
		re_cnt++;
	}
	return (0);
}

void	recover_dque(t_deque *dque, int re_cnt)
{
	t_list	*token;

	while (re_cnt > 0)
	{
		token = dque->pop_rear(dque);
		dque->push_front(dque, token);
		re_cnt--;
	}
}
