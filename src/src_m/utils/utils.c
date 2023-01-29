/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:47:10 by jgo               #+#    #+#             */
/*   Updated: 2023/01/29 15:32:21 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"

t_meta  *get_meta(void)
{
	static t_meta *meta;

	if (meta != NULL)
		return (meta);
	meta = ft_malloc(sizeof(t_meta));
	return (meta);
}

void	envp_init(char **envp)
{
	t_meta *meta;
	int	i;

	meta = get_meta();
	i = -1;
	while(envp[++i])
		ft_lstadd_back(&meta->envp, ft_lstnew(ft_split(envp[i], '=')));
}
