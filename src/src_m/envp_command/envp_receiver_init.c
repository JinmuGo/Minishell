/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_receiver_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:58:23 by jgo               #+#    #+#             */
/*   Updated: 2023/03/11 11:35:02 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "meta_command.h"
#include "envp_command.h"

char	*get_envp_key(char *envp_elem)
{
	char	*key;
	int		i;

	i = -1;
	while (envp_elem[++i])
		if (envp_elem[i] == '=')
			break ;
	key = ft_substr(envp_elem, 0, i);
	return (key);
}

char	*get_envp_val(char *envp_elem)
{
	char	*tmp;
	char	*val;

	tmp = ft_strchr(envp_elem, '=');
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		return (NULL);
	}
	tmp += 1;
	val = ft_strdup(tmp);
	return (val);
}

void	envp_init(char **envp)
{
	char	*key;
	char	*val;
	int		i;

	i = -1;
	while (envp[++i])
	{
		key = get_envp_key(envp[i]);
		val = get_envp_val(envp[i]);
		if (ft_strlen(key) && ft_strlen(val) && ft_strcmp(key, "OLDPWD"))
			set_envp_elem(key, val);
		else
			ft_free_n(2, key, val);
	}
}
