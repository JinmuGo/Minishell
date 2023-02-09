/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:47:10 by jgo               #+#    #+#             */
/*   Updated: 2023/02/09 20:41:25 by jgo              ###   ########.fr       */
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

char	**split_envp(char *envp_elem)
{
	int	i;
	char **rv;

	i = -1;
	while (envp_elem[++i])
		if (envp_elem[i] == '=')
			break;
	rv = ft_malloc(sizeof(char *) * 2);
	rv[0] = ft_substr(envp_elem, 0, i);
	rv[1] = ft_strchr(envp_elem, '=');
	rv[1] += 1;
	return (rv);
}

void	envp_init(char **envp)
{
	t_meta *meta;
	t_envp	*envp_tmp;
	char **arr;
	int	i;

	meta = get_meta();
	i = -1;
	while(envp[++i])
	{
		arr = split_envp(envp[i]);
		envp_tmp = ft_malloc(sizeof(t_envp));
		envp_tmp->key = arr[0];
		envp_tmp->val = arr[1];
		envp_tmp->val_len = ft_strlen(envp_tmp->val);
		ft_lstadd_back(&meta->envp, ft_lstnew(envp_tmp));
	}
}

char	*get_envp_value(char *key)
{
	char *value;


	return (value);
}