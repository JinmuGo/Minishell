/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:50:25 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/12 15:46:49 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "data_structure.h"

void	*dq_peek_front(const t_deque *dque)
{
	if (dque->use_size)
		return (dque->nodes[dque->front]);
	else
		return (NULL);
}

void	*dq_peek_rear(const t_deque *dque)
{
	if (dque->use_size)
		return (dque->nodes[dque->rear]);
	else
		return (NULL);
}

void	dq_free(const t_deque *dque)
{
	size_t	i;

	i = 0;
	while (i < dque->use_size)
	{
		free(dque->nodes[(i + dque->front) % dque->capacity]);
		i++;
	}
	free(dque->nodes);
	free((void *)dque);
}

void	dq_clear(t_deque *dque)
{
	while (dque->use_size > 0)
		dque->pop_front(dque);
}
