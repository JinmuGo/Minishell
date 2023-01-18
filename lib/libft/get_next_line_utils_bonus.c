/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:51 by jgo               #+#    #+#             */
/*   Updated: 2022/11/17 11:04:32 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*free_lst_elem(t_buf **buf_lst, t_buf *buf)
{	
	t_buf	*cur;
	t_buf	*prev;

	prev = NULL;
	cur = *buf_lst;
	while (cur)
	{
		if (cur == buf)
		{
			if (prev)
				prev->next = cur->next;
			else
			{
				if (*buf_lst)
					*buf_lst = cur->next;
			}
			free(cur);
			return (NULL);
		}
		prev = cur;
		cur = cur->next;
	}
	if ((buf && !buf->buf_str[buf->endpoint]) || (buf && buf->position == HEAD))
		free(buf);
	return (NULL);
}

size_t	get_total_len(t_buf *buf)
{
	size_t		total_len;
	const int	first_fd = buf->fd;

	total_len = 0;
	while (buf && buf->fd == first_fd)
	{
		total_len += buf->endpoint;
		buf = buf->next;
	}
	return (total_len);
}

size_t	put_in_str2(char *str, size_t iter, t_buf *buf, size_t total_len)
{
	while (iter <= buf->endpoint && buf->buf_str[iter] != '\0')
	{
		str[total_len + iter] = buf->buf_str[iter];
		iter++;
	}
	return (iter);
}

char	*put_in_str(t_buf **buf_lst, t_buf *buf, char *str, size_t total_len)
{
	size_t		endpoint;
	t_buf		*temp_buf;
	const int	first_fd = buf->fd;

	temp_buf = buf;
	endpoint = 0;
	while (buf)
	{
		if (temp_buf && temp_buf->fd == first_fd)
			temp_buf = buf->next;
		else
			break ;
		total_len -= buf->endpoint;
		endpoint += put_in_str2(str, 0, buf, total_len);
		if (buf->position)
			free_lst_elem(buf_lst, buf);
		else
			free(buf);
		buf = temp_buf;
	}
	str[endpoint] = '\0';
	return (str);
}

char	*make_str(t_buf **buf_lst, t_buf *buf)
{
	char			*str;
	const size_t	total_len = get_total_len(buf);

	str = malloc(sizeof(char) * (total_len + 2));
	if (!str)
		return (NULL);
	str = put_in_str(buf_lst, buf, str, total_len);
	if (!str)
		return (NULL);
	return (str);
}
