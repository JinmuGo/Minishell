/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:53 by jgo               #+#    #+#             */
/*   Updated: 2023/02/23 18:31:50 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef enum e_kind {
	HEAD = 1,
	TAIL = 0
}	t_kind;

typedef struct s_buf
{
	int				fd;
	size_t			endpoint;
	ssize_t			read_size;
	char			buf_str[BUFFER_SIZE + 1];
	t_kind			position;
	struct s_buf	*next;
}	t_buf;

char	*get_next_line(int fd);
void	*free_lst_elem(t_buf **buf_lst, t_buf *buf);
size_t	get_total_len(t_buf *buf);
char	*put_in_str(t_buf **buf_lst, t_buf *buf, char *str, size_t total_len);
char	*make_str(t_buf **buf_lst, t_buf *buf);

#endif
