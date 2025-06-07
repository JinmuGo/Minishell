/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:10:04 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/12 15:47:03 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

t_deque	*deque_init(size_t size);
void	dq_push_front(t_deque *dque, void *data);
void	dq_push_rear(t_deque *dque, void *data);
void	*dq_pop_front(t_deque *dque);
void	*dq_pop_rear(t_deque *dque);
void	dq_clear(t_deque *dque);

#endif