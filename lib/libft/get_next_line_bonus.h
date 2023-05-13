/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:53 by jgo               #+#    #+#             */
/*   Updated: 2023/04/18 16:48:37 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

/*-------------- INCLUDE --------------*/
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/*-------------- TYPEDEF --------------*/
typedef enum e_edge		t_edge;
typedef struct s_buf	t_buf;

/*--------------  ENUM  --------------*/
enum e_edge {
	TAIL,
	HEAD
};

/*-------------- STRUCT --------------*/
struct s_buf
{
	int				fd;
	size_t			endpoint;
	ssize_t			read_size;
	char			buf_str[BUFFER_SIZE + 1];
	t_edge			position;
	struct s_buf	*next;
};

/*-------- FUNCTION_PROTOTYPE ---------*/
char	*get_next_line(int fd);
void	*free_lst_elem(t_buf **buf_lst, t_buf *buf);
char	*make_str(t_buf **buf_lst, t_buf *buf);

#endif
