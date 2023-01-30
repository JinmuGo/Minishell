/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:55:26 by jgo               #+#    #+#             */
/*   Updated: 2023/01/30 21:16:58 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct stack
{
    t_list arr; // malloc arr.content int
    int size;
    push();
    pop();
    size();
};

typedef struct stack t_stack;

int tokenizer()
{
    t_stack stack;
    int a;

    a = 3;
    arr.content = malloc(sizeof(int));
    *(arr.content) = a;

    stack.push(a);
    
}