/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:40:05 by jgo               #+#    #+#             */
/*   Updated: 2023/02/25 12:03:20 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include "envp_command.h"
#include "built_in.h"
#include "meta_command.h"


// https://www.geeksforgeeks.org/shell-scripting-rules-for-naming-variable-name/
// Rule 1: A variable name can have letters, numbers, and underscores
// Rule 3: The  variable name cannot have special characters
// Rule 4: The first character of the variable name cannot be a number
// Rule 5: Variable names cannot be reserved words // 그러나 expanding은 되기 때문에 expanding한다.
// Rule 6: Variable name cannot have whitespace in between

//  export asdf 뒤에 인자가 없는 경우 실패도 아니고 아무 동작도 하지않고 끝난다.  

void	append_val(char *tmp, char *src)
{
	const char *key = ft_strtrim(tmp, "+");
	const char *dst = get_envp_elem(key)->val;
	const char *val = ft_strjoin(dst, src);
	const char *prev_key = get_envp_elem(key)->key;

	set_envp_elem(key, val);
	if (prev_key)
		free((void *)prev_key);
	free((void *)dst);
	free(tmp);
	free(src);
}

t_bool  exec_export(char *arg)
{
    char *key;
    char *val;
	int	len;
    int i;

    key = get_envp_key(arg);
	len = ft_strlen(key);
    if (ft_isdigit(arg[0]) || len == 0)
	{
		free(key);
        return (print_built_in_err("export ", arg, ERR_INVALID_IDENT));
	}
    i = -1;
    while (key[++i])
        if (!is_valid_params(key[i]) && key[len - 1] != '+')
		{
			free(key);
            return (print_built_in_err("export ", arg, ERR_INVALID_IDENT));
		}
	val = get_envp_val(arg);
    if (key[len - 1] == '+')
		append_val(key, val);
	else if (ft_strchr(arg, '='))
        set_envp_elem(key, val);
    return (FT_TRUE);
}

void ft_export(t_simple_cmd *simple_cmd)
{
    int i;

    i = 0;
	

    while (simple_cmd->args[++i])
        if (exec_export(simple_cmd->args[i]))
			set_exit_status(EXIT_SUCCESS);
}