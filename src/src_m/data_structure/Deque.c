/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:13:49 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/06 16:52:06 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "data_structure.h"

t_deque	*deque_init(size_t size)
{
	t_deque	*dque;

	dque = ft_malloc(sizeof(t_deque));
	dque->capacity = size;
	dque->front = 0;
	dque->rear = 0;
	dque->use_size = 0;
	dque->nodes = ft_calloc(sizeof(void *), dque->capacity);
	dque->push_front = dq_push_front;
	dque->push_rear = dq_push_rear;
	dque->pop_front = dq_pop_front;
	dque->pop_rear = dq_pop_rear;
	dque->peek_front = dq_peek_front;
	dque->peek_rear = dq_peek_rear;
	return (dque);
}

void	dq_push_front(t_deque *dque, void *data)
{
	size_t	tmp;

	if (dque->use_size == 0)
		tmp = dque->front;
	else if (dque->front == 0)
		tmp = dque->capacity - 1;
	else
		tmp = dque->front - 1;
	dque->nodes[tmp] = data;
	dque->front = tmp;
	dque->use_size++;
}

void	dq_push_rear(t_deque *dque, void *data)
{
	size_t	tmp;

	if (dque->use_size == 0)
		tmp = dque->rear;
	else if (dque->rear == dque->capacity - 1)
		tmp = 0;
	else
		tmp = dque->rear + 1;
	dque->nodes[tmp] = data;
	dque->rear = tmp;
	dque->use_size++;
	return ;
}

void	*dq_pop_front(t_deque *dque)
{
	size_t	tmp;
	void	*data;

	if (dque->front == dque->capacity - 1)
		tmp = 0;
	else
		tmp = dque->front + 1;
	data = dque->nodes[dque->front];
	if (dque->front != dque->rear)
		dque->front = tmp;
	dque->use_size--;
	return (data);
}

void	*dq_pop_rear(t_deque *dque)
{
	size_t	tmp;
	void	*data;

	if (dque->rear == 0)
		tmp = dque->capacity - 1;
	else
		tmp = dque->rear - 1;
	data = dque->nodes[dque->rear];
	if (dque->front != dque->rear)
		dque->rear = tmp;
	dque->use_size--;
	return (data);
}
