/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:51:55 by jgo               #+#    #+#             */
/*   Updated: 2023/02/23 21:56:59 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

void    rdr_in(t_rdr *rdr)
{
    const int fd = open(rdr->file, O_RDONLY, 0644);

    dup2(fd, STDIN_FILENO);
}

void    rdr_out(t_rdr *rdr)
{
    const int fd = open(rdr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    dup2(fd, STDOUT_FILENO);
}

void    rdr_append(t_rdr *rdr)
{
    const int fd = open(rdr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);

    dup2(fd, STDOUT_FILENO);
}

void    rdr_heredoc(t_rdr *rdr)
{
    // here_doc은 open 할 필요없다. (특별하게 처리)

    // unlink_lst를 이용해 unlink할 것.
}

void    rdr_executor(t_rdr *rdr)
{
    const t_rdr_func fp = {rdr_in, rdr_out, rdr_append, rdr_heredoc};

    fp[rdr->rdr_type](rdr);
}

