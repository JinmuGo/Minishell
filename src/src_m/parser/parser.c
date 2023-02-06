/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:46:50 by jgo               #+#    #+#             */
/*   Updated: 2023/02/06 21:17:41 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include "defines.h"

t_tree	*parser(void)
{
	t_tree	*tree;
	t_list	*tk_list;

	tk_list = tokenize(tk_list);
	// 토큰리스트 를 순회하면서 bnf 확인하기
	// 토큰종류 (pipe, rdr, s_cmd)
	// tree노드 종류 (pipe, CMD(rdr, s_cmd))
	// '|'(root)노드를 먼저 하나 넣어놓고, \
		CMD노드에 리다이렉션과 s_cmd넣어주기
	// 파이프 확인
	// 리다이렉션, 파일유무 확인
		// 리다이렉션 뒤에는 file이 와야한다.
	// 명령어, 인자 확인
		// 리다이렉션과 file 제외한 첫번째 word가 cmd_name이 된다. 나머지는 cmd_args로 한다.
	free_tk_list(&tk_list);
	return (tree);
}
