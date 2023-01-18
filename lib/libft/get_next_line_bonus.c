/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:06:38 by jgo               #+#    #+#             */
/*   Updated: 2022/11/17 11:04:29 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_buf	*add_new_buf(t_buf *buf, int fd)
{
	t_buf	*new_buf;

	new_buf = malloc(sizeof(t_buf));
	if (!new_buf)
		return (NULL);
	new_buf->fd = fd;
	new_buf->next = buf;
	new_buf->endpoint = 0;
	new_buf->position = TAIL;
	new_buf->read_size = read(fd, new_buf->buf_str, BUFFER_SIZE);
	if (new_buf->read_size <= 0)
	{
		free(new_buf);
		return (NULL);
	}
	new_buf->buf_str[new_buf->read_size] = '\0';
	return (new_buf);
}

t_buf	*find_fd_or_create(t_buf **head, t_buf *cur, t_buf *node, int fd)
{
	while (cur)
	{
		if (cur->fd == fd)
		{
			if (node)
				node -> next = cur -> next;
			else
				*head = cur;
			return (cur);
		}
		if (!cur->next)
			break ;
		node = cur;
		cur = cur->next;
	}
	node = add_new_buf(NULL, fd);
	if (!node)
		return (free_lst_elem(head, node));
	if (cur)
		cur -> next = node;
	else
		*head = node;
	return (node);
}

t_buf	*read_untill_endpoint(t_buf *buf)
{
	size_t	idx;
	t_buf	*prev;

	prev = NULL;
	while (buf)
	{
		idx = -1;
		while (buf->buf_str[++idx] != '\n' && buf->buf_str[idx] != '\0')
			continue ;
		buf->endpoint = idx;
		if (buf->buf_str[idx] == '\n')
			return (buf);
		else
		{
			prev = buf;
			buf = add_new_buf(buf, buf->fd);
			if (!buf)
				return (prev);
		}
	}
	return (buf);
}

void	restore_buf(t_buf **head, t_buf *buf, t_buf *restore_buf, size_t iter)
{
	if (buf->buf_str[buf->endpoint] == '\0')
		return ;
	restore_buf = malloc(sizeof(t_buf));
	if (!restore_buf)
		return ;
	iter = 0;
	while (buf->endpoint + iter + 1 <= (size_t)buf->read_size
		&& buf->buf_str[buf->endpoint + iter + 1] != '\0')
	{
		restore_buf->buf_str[iter] = buf->buf_str[buf->endpoint + iter + 1];
		iter++;
	}
	if (restore_buf->buf_str[0] == '\0' || iter == 0)
	{
		free(restore_buf);
		return ;
	}
	restore_buf->fd = buf->fd;
	restore_buf->next = *head;
	restore_buf->buf_str[iter] = '\0';
	restore_buf->endpoint = 0;
	restore_buf->read_size = iter;
	*head = restore_buf;
}

char	*get_next_line(int fd)
{
	static t_buf	*buf_lst;
	t_buf			*buf;
	char			*str;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buf = find_fd_or_create(&buf_lst, buf_lst, NULL, fd);
	if (!buf)
		return (NULL);
	buf->position = HEAD;
	buf = read_untill_endpoint(buf);
	if (!buf)
		return (free_lst_elem(&buf_lst, buf));
	restore_buf(&buf_lst, buf, NULL, 0);
	str = make_str(&buf_lst, buf);
	return (str);
}
