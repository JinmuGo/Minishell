/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:52:37 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/01 21:30:52 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "stack.h"
#include "parser.h"
#include "util.h"

t_list	*tokenize(char *line)
{
	t_list	*tk_list;

	tk_list = ft_malloc(sizeof(t_list));
	make_tk_list(tk_list, line);
	return (tk_list);
}

void	make_tk_list(t_list *tk_list, char *line)
{
	// list만들기 재귀 
		// 문자열 종료시 탈출
		// 공백 넘어가기 (line++)
		// WORD 처리 (|, <, >, <<, >>, 공백) 만날때까지
			// quote 처리
				// stack 으로 짝 확인하기 (size++)
		// 파이프 처리 (line++)
		// 리다이렉션 처리 (rdr_type 구분해서 저장) (line++)
		// list만들기 재귀 (tk_list, (&line + size))
}
