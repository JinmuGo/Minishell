/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:39:44 by jgo               #+#    #+#             */
/*   Updated: 2023/02/09 19:38:13 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinsert(char **arr, char *insert)
{
	char	*str;
	char	*tmp;
	int		idx;

	idx = 0;
	str = ft_strjoin(arr[idx], "");
	while (arr[idx + 1] != NULL)
	{
		tmp = str;
		str = ft_strjoin(str, insert);
		free(tmp);
		tmp = str;
		str = ft_strjoin(str, arr[idx + 1]);
		free(tmp);
		idx++;
	}
	return (str);
}
