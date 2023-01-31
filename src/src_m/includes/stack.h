/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:19:44 by sanghwal          #+#    #+#             */
/*   Updated: 2023/01/31 20:22:36 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

/* stack.c */
void	stack_init(t_stack *stack);
void	stack_push(t_stack *stack, void *value);
void	*stack_pop(t_stack *stack);
void	*stack_peek(t_stack *stack);
void	test_stack(void);

#endif