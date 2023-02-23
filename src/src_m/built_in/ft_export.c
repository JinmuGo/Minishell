/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:40:05 by jgo               #+#    #+#             */
/*   Updated: 2023/02/09 17:40:18 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

// https://www.geeksforgeeks.org/shell-scripting-rules-for-naming-variable-name/
// Rule 1: A variable name can have letters, numbers, and underscores
// Rule 3: The  variable name cannot have special characters
// Rule 4: The first character of the variable name cannot be a number
// Rule 5: Variable names cannot be reserved words // 그러나 expanding은 되기 때문에 expanding한다.
// Rule 6: Variable name cannot have whitespace in between
t_bool	is_valid_params(char *str)
{
	
	
}
