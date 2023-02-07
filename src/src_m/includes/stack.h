/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:19:44 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/07 17:51:02 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

/* stack.c */
void	stack_init(t_stack *stack);
void	stack_push(t_stack *stack, void *value);
void	*stack_pop(t_stack *stack);
void	*stack_peek(t_stack *stack);
void	stack_destory(t_stack *stack);
t_bool  stack_is_empty(t_stack *stack);

#endif