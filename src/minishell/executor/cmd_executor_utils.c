/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:16:00 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:34:16 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"

const char	**get_path_arr(void)
{
	const t_hash_elem	*elem = get_envp_elem("PATH");

	if (elem)
		return ((const char **)ft_split(elem->val, ':'));
	else
		return (NULL);
}

char	*make_abs_path(char *cmd, const char **path_arr)
{
	char	*rv;
	char	*tmp;
	int		i;

	if (!path_arr || ft_strchr(cmd, '.') || ft_strchr(cmd, '/'))
		return (cmd);
	i = -1;
	while (path_arr[++i])
	{
		tmp = ft_strjoin(path_arr[i], "/");
		rv = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(rv, F_OK | X_OK) == 0)
			return (rv);
		free(rv);
	}
	return (NULL);
}

const char	**make_envp_arr(t_tree_node *node)
{
	t_simple_cmd	*simple_cmd;
	t_hash_elem		*elem;
	int				val;

	if (node == NULL)
		return (NULL);
	simple_cmd = ((t_token *)(node->value))->cmd_val.simple_cmd;
	if (simple_cmd == NULL || ft_strcmp(simple_cmd->cmd, "./minishell"))
		return (NULL);
	elem = get_envp_elem("SHLVL");
	if (elem)
	{
		val = ft_atoi(elem->val);
		set_envp_elem(ft_strdup("SHLVL"), ft_itoa(val + 1));
	}
	else
		set_envp_elem(ft_strdup("SHLVL"), ft_itoa(1));
	return ((const char **)convert_char_arr());
}
