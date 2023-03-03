/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:03:30 by jgo               #+#    #+#             */
/*   Updated: 2023/03/03 21:29:24 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

t_token_type	check_token_type(t_tree_node *node)
{
	if (node == NULL)
		return (NONE);
	return (((t_token *)(node->value))->type);
}