/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:51:43 by jgo               #+#    #+#             */
/*   Updated: 2023/02/23 21:02:19 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "executor.h"
#include "built_in.h"

void	s_cmd_executor(t_simple_cmd *simple_cmd)
{
	const t_simple_cmd_type type = is_built_in_cmd(simple_cmd->cmd);

	if (type != FT_EXTERNAL)
		built_in(simple_cmd, type);
		
}