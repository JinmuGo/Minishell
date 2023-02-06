/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:47:10 by jgo               #+#    #+#             */
/*   Updated: 2023/02/05 18:32:18 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"

t_meta	*get_meta(void)
{
	static t_meta	*meta;

	if (meta != NULL)
		return (meta);
	meta = ft_malloc(sizeof(t_meta));
	return (meta);
}

void	envp_init(char **envp)
{
	t_meta	*meta;
	int		i;

	meta = get_meta();
	i = -1;
	while (envp[++i])
		ft_lstadd_back(&meta->envp, ft_lstnew(ft_split(envp[i], '=')));
}
