/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:55:26 by jgo               #+#    #+#             */
/*   Updated: 2023/01/31 17:32:53 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"

void	stack_init(t_stack *stack)
{
	stack->arr = NULL;
	stack->size = 0;
	stack->push = stack_push;
	stack->pop = stack_pop;
}

void	stack_push(t_stack *stack, void *value)
{
	ft_lstadd_front(&stack->arr, ft_lstnew(value));
	stack->size++;
}

void	*stack_pop(t_stack *stack)
{
	void	*value;
	t_list	*tmp;

	value = NULL;
	if (stack && stack->size > 0)
	{
		value = stack->arr->content;
		tmp = stack->arr->next;
	/*	free(stack->arr.content);
		general한 stack라이브러리를 위해서는 content의 malloc 필요? */
		free(stack->arr);
		stack->arr = tmp;
		stack->size--;
	}
	return (value);
}

void	*stack_peek(t_stack *stack)
{
	return (stack->arr->content);
}

void	test_stack(void)
{
	t_stack	stack;
	void	*val;

	stack_init(&stack);
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			val = D_QUOTE;
		else
			val = S_QUOTE;
		stack.push(&stack, val);
		printf("stack_push(%d): %s\n", i, stack.arr->content);
	}
	for (int i = 0; i < 10; i++)
	{
		val = stack.pop(&stack);
		printf("stack_pop(%d): %s\n", i, val);
	}
}
