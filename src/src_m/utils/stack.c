/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:55:26 by jgo               #+#    #+#             */
/*   Updated: 2023/01/30 22:03:49 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

struct stack
{
	t_list	arr; // malloc arr.content int
	int size;
	// push();
	// pop();
	// size();
};

typedef struct stack t_stack;

int tokenizer()
{
	t_stack stack;
	char	*a;

	a = D_QUOTE;
	// stack.arr = (t_list *)malloc(sizeof(t_list));
	stack.arr.content = (char *)malloc(sizeof(char *));
	stack.arr.content = a;
	printf("%s", stack.arr.content);
}
