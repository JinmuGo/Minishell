/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:42:45 by jgo               #+#    #+#             */
/*   Updated: 2023/02/18 21:05:31 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "data_structure.h"

t_bool    is_same_quote(t_bool quote, char c, char *tmp)
{
    if (*tmp == c)
        return (quote);
    else
    {
        *tmp = c;
        return (!quote);
    }
}

int cal_remove_len(char *str)
{
    t_bool quote;
    char tmp;
    int len;
    int i;

    len = 0;
    i = -1;
    quote = FT_FALSE;
    tmp = 0;
    while(str[++i])
    {
        if (str[i] == S_QUOTE || str[i] == D_QUOTE)
            quote = is_same_quote(quote, str[i], &tmp);
        else
        {
            if (quote)
                len++;
        }
    }
    return (len);
}

char *quote_removal(char *str)
{
    const int len = cal_remove_len(str);

    printf("quote_removal len : %d\n", len);
    return (str);
}