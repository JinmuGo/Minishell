/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:46:50 by jgo               #+#    #+#             */
/*   Updated: 2023/02/07 19:27:22 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include "defines.h"
#include "tree.h"

t_tree	*parser(char *line)
{
	t_tree	*tree;
	t_list	*tk_list;

	tk_list = tokenize(line);
	tree = malloc(sizeof(t_tree));
	tree_init(tree);
	make_tree(tree, tk_list);
	// tree->value == (t_token *)
	// 토큰종류 (pipe, rdr, s_cmd)
	// tree노드 종류 (pipe, CMD(rdr, s_cmd))
	// 리다이렉션, 파일유무 확인
		// 리다이렉션 뒤에는 file이 와야한다.
	// 명령어, 인자 확인
		// 리다이렉션과 file 제외한 첫번째 word가 cmd_name이 된다. 나머지는 cmd_args로 한다.
	free_tk_list(&tk_list);
	return (tree);
}

void	make_tree(t_tree *tree, t_list *tk_list)
{
	insert_root(tree);
}

// void	insert_root(t_tree *tree)
// {
// 	tree->root = 
// }
// 트리에 넣을 노드를 tk_list로 전달받아야한다. -> delte_lst_node 를 위해서는 head 의 주소가 필요하다;;;
t_token	*make_value(t_list *tk_list, t_tokenize *token)
{
	t_token	*value;

	value = malloc(sizeof(t_token));
	if (!token || token->type == PIPE)
		set_pipe(tk_list, token, value);
	else if (token->type == RDR)
		set_rdr(tk_list, token, value);
	else if (token->type == WORD)
		set_simple_cmd(tk_list, token, value);
	return (value);
}
// 인자로 받는 tk_list는 트리에 넣을 해당 노드이다.
void	set_rdr(t_list *tk_list, t_tokenize *token , t_token *value)
{
	if (token->str == '<')
		value->cmd_val.rdr->rdr_type = IN;
	else if (token->str == '>')
		value->cmd_val.rdr->rdr_type = OUT;
	else if (token->str == '>>')
		value->cmd_val.rdr->rdr_type = APPEND;
	else if (token->str == '<<')
		value->cmd_val.rdr->rdr_type = HEREDOC;
	delete_lst_node(tk_list, token);
	token = tk_list->content;
	if (token->type == WORD)
	{
		value->cmd_val.rdr->file = ft_strdup(token->str);
		delete_lst_node(tk_list, token);
		return ;
	}
	value->cmd_val.rdr->file = NULL;
}

void	set_pipe(t_list *tk_list, t_tokenize *token , t_token *value)
{
	value->type = PIPE;
	value->cmd_val.pipe->fd[0] = 0;
	value->cmd_val.pipe->fd[1] = 0;
	delete_lst_node(tk_list, token);
}

void	delete_lst_node(t_list *tk_list, t_tokenize *token)
{
	t_list	*head_tmp;
	t_list	*pre_tmp;

	head_tmp = tk_list;
	if (head_tmp->content == token)
	{
		tk_list = head_tmp->next;
		free_token_str(head_tmp->content);
		free(head_tmp);
	}
	else
	{
		while (head_tmp->next->content != token)
			head_tmp = head_tmp->next;
		pre_tmp = head_tmp;
		pre_tmp->next = head_tmp->next->next;
		free_token_str(head_tmp->next->content);
		free(head_tmp->next);
	}
}