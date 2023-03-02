/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:03:30 by jgo               #+#    #+#             */
/*   Updated: 2023/03/02 17:12:00 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

t_token_type	check_token_type(t_tree_node *node)
{
	const t_token *token = (t_token *)(node->value);

	if (token)
		return (((t_token *)(node->value))->type);
	else
		return (NONE);
}