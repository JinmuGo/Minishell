/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:16:31 by jgo               #+#    #+#             */
/*   Updated: 2023/02/13 14:54:52 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

t_bool is_shell_var(char c)
{
    if (c == '_')
        return (FT_TRUE);
    if (ft_isspecial(c) || c == '\0')
        return (FT_FALSE);
    return (FT_TRUE);
}