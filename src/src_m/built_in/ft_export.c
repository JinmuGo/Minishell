/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:40:05 by jgo               #+#    #+#             */
/*   Updated: 2023/02/24 18:23:20 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "error.h"
#include "envp_command.h"


// https://www.geeksforgeeks.org/shell-scripting-rules-for-naming-variable-name/
// Rule 1: A variable name can have letters, numbers, and underscores
// Rule 3: The  variable name cannot have special characters
// Rule 4: The first character of the variable name cannot be a number
// Rule 5: Variable names cannot be reserved words // 그러나 expanding은 되기 때문에 expanding한다.
// Rule 6: Variable name cannot have whitespace in between

//  export asdf 뒤에 인자가 없는 경우 실패도 아니고 아무 동동작작도 하지않고 끝난다.  
t_bool	is_valid_params(char c)
{
	if (c == '_')
        return (FT_TRUE);
    if (ft_isspecial(c) || c == '\0')
        return (FT_FALSE);
    return (FT_TRUE);
}

t_bool  exec_export(char *arg)
{
    char *key;
    char *val;
    int i;

    if (ft_isalnum(arg[0]))
        return (print_built_in_err("export", arg,"not a valid identifier"));
    i = 0;
    if ()
    if (ft_strchr(arg, '='))
    {
        key = get_envp_key(arg);
		val = get_envp_val(arg);
        set_envp_elem(key, val);
    }
}

void ft_export(t_simple_cmd *simple_cmd)
{
    int i;

    i = 0;
    while (simple_cmd->args[++i])
    {
        exec_export(simple_cmd->args[i]);
    }
}