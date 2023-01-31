/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:35 by jgo               #+#    #+#             */
/*   Updated: 2023/01/31 17:10:33 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* utils.c */

t_meta	*get_meta(void);
void	envp_init(char **envp);

/* stack.c */
void	stack_init(t_stack *stack);
void	stack_push(t_stack *stack, void *value);
void	*stack_pop(t_stack *stack);
void	*stack_peek(t_stack *stack);

/* input.c */

void	prompt(void);

/* signal.c */

void	signal_process(int signum);

// debug.c

void	print_list(void *content);

#endif