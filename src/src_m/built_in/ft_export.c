/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:40:05 by jgo               #+#    #+#             */
/*   Updated: 2023/03/16 19:55:47 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include "envp_command.h"
#include "meta_command.h"
#include "built_in.h"
#include "expander.h"

void	append_val(char *tmp, char *src)
{
	const char			*key = ft_strtrim(tmp, "+");
	const t_hash_elem	*elem = get_envp_elem(key);
	char				*val;

	if (elem)
	{
		val = ft_strjoin(elem->val, src);
		set_envp_elem(key, val);
	}
	else
		set_envp_elem(key, ft_strdup(src));
	free(tmp);
	free(src);
}

t_bool	judge_export_param(char *arg, char *key, const int len)
{
	int	i;

	if (ft_isdigit(arg[0]) || len == 0)
	{
		free((void *)key);
		return (prt_built_in_err(\
			"export ", arg, ERR_INVALID_IDENT, EXIT_FAILURE));
	}
	i = -1;
	while (key[++i])
	{
		if (!is_valid_params(key[i]) && key[len - 1] != '+')
		{
			free((void *)key);
			return (prt_built_in_err(\
				"export ", arg, ERR_INVALID_IDENT, EXIT_FAILURE));
		}
	}
	return (FT_TRUE);
}

t_bool	exec_export(char *arg, char *key)
{
	const int	len = ft_strlen(key);
	char		*val;

	if (judge_export_param(arg, key, len) == FT_FALSE)
		return (FT_FALSE);
	val = get_envp_val(arg);
	if (val == NULL)
	{
		free((void *)key);
		return (FT_TRUE);
	}
	if (key[len - 1] == '+')
		append_val(key, val);
	else if (ft_strchr(arg, '='))
		set_envp_elem(key, val);
	return (FT_TRUE);
}

int	ft_export(t_simple_cmd *simple_cmd)
{
	const int	len = ft_arrlen((void **)simple_cmd->args);
	int			i;

	i = 0;
	if (len == 1)
		print_envp_elem("declare -x");
	else
	{
		while (simple_cmd->args[++i])
		{
			if (exec_export(\
				simple_cmd->args[i], get_envp_key(simple_cmd->args[i])))
				continue ;
			else
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
