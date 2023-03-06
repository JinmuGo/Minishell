/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:51:28 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/06 16:51:44 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "data_structure.h"

t_bool	stack_is_empty(t_stack *stack)
{
	if (stack->size)
		return (FALSE);
	else
		return (TRUE);
}
