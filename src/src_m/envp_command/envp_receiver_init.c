/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_receiver_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:58:23 by jgo               #+#    #+#             */
/*   Updated: 2023/02/24 17:25:29 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "envp_command.h"

char	*get_envp_key(char *envp_elem)
{
	int	i;
	char *key;

	i = -1;
	while (envp_elem[++i])
		if (envp_elem[i] == '=')
			break;
	key = ft_substr(envp_elem, 0, i);
	return (key);
}

char	*get_envp_val(char *envp_elem)
{
	char *tmp;
	char *val;

	tmp = ft_strchr(envp_elem, '=');
	tmp += 1;
	val = ft_strdup(tmp);
	return (val);
}

void	envp_init(char **envp)
{
	char *key;
	char *val;
	int	i;

	i = -1;
	while(envp[++i])
	{
		key = get_envp_key(envp[i]);
		val = get_envp_val(envp[i]);
		set_envp_elem(key, val);
	}
}
