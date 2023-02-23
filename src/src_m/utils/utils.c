/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:47:10 by jgo               #+#    #+#             */
/*   Updated: 2023/02/23 17:53:17 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "envp_command.h"
#include "meta_command.h"

void	set_status(int n)
{
	t_meta *meta;
	char	*nb;
	char	*res;

	meta = get_meta();
	nb = ft_itoa(n);
	meta->exit_status = n;
	set_envp_elem("?", nb);
}

char *get_cur_dir(void)
{
	char	buffer[1000];
	char	*dst;

	getcwd(buffer, 1000);
	dst = ft_strdup(buffer);
	return (dst);
}
