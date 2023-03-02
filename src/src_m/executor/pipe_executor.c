/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:51:49 by jgo               #+#    #+#             */
/*   Updated: 2023/03/01 22:41:12 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include <errno.h>

void	pipe_executor(t_pipe *_pipe)
{
    print_system_call_err(pipe(_pipe->fd)); // execute구조체에 pipe의 fd를 queue같은 거에다 저장하고 pop하면서 실행 후 삭제하면 좋을듯?!
}

