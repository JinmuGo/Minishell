/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:46:50 by jgo               #+#    #+#             */
/*   Updated: 2023/02/09 21:57:09 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "tree.h"
#include "deque.h"

t_tree	*parser(char *line)
{
	t_tree	*tree;
	t_list	*tk_list;

	tk_list = tokenize(line);
	tree = malloc(sizeof(t_tree));
	tree_init(tree);
	make_tree(tree, tk_list, 0, 0);
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

void	make_tree(t_tree *tree, t_list *tk_list, t_list *cur_list, t_tree_node *cur_node)
{
	t_deque		*dque;

	if (!cur_list && !tk_list)
		cur_list = tk_list;
	if (!tree->root)
		insert_root(tree);
	if (!cur_node && !tree->root)
		cur_node = tree->root;
	if (!cur_node)
		return ;
	save_dque(tk_list, &cur_list, dque);
	dque_to_tree(tree, tk_list, cur_node, dque);
	make_tree(tree, tk_list, cur_list, cur_node->right);
}
//  dque의 내용들을 t_token형태로 만들고 t_tree_node의 value에 연결해준다.
void	dque_to_tree(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	make_left(tree, tk_list, cur_node, dque);
	make_right(tree, tk_list, cur_node, dque);
}

void	make_left(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	if (cur_node == tree->root)
		return ;
	if (((t_token *)(cur_node->value))->type == PIPE)
		// CMD 노드 만들여부 체크 && 만들어서 dque_to_tree(cur_node = CMD)
	if (((t_token *)(cur_node->value))->type == CMD)
		// RDR 노드 만들여부 체크 && 만들어서 dque_to_tree(cur_node = RDR)
	if (((t_token *)(cur_node->value))->type = RDR)
		// dque에 RDR타입이 있는지 탐색해서 RDR 만들고 다시 dque_to_tree(cur_node = RDR)
}

void	make_right(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	if (((t_token *)(cur_node->value))->type == RDR)
		// 탈출
	if (((t_token *)(cur_node->value))->type == PIPE)
		// CMD or PIPE 만들어서 dque_to_tree(cur_node = CMD or PIPE)
	elseif (((t_token *)(cur_node->value))->type == CMD)
		// s_cmd 노드 만드여부 체크 && 만들어서 탈출 (하나의 CMD에는 하나의 s_cmd만 온다)
}
// PIPE노드를 만들어서 insert하는 함수
t_tree_node	*insert_pipe_node(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_token		*value;
	t_tokenize	*token;
	t_tree_node	*new_node;

	token = ((t_list *)(dque->pop_front(dque)))->content;
	value = make_value(tk_list, token, dque);
	new_node = create_node(value);
	insert(cur_node, RIGHT, new_node);
	return(new_node);
}
// CMD 노드를 만들어서 insert하는 함수
t_tree_node	*insert_cmd_node(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_token		*value;
	t_tokenize	*token;
	t_tree_node	*new_node;

	value = ft_malloc(sizeof(t_token));
	value->type = CMD;
	new_node = create_node(value);
	if (cur_node->left == NULL)
		insert(cur_node, LEFT, new_node);
	else
		insert(cur_node, RIGHT, new_node);
	return (new_node);
}
// RDR 노드를 만들어서 insert하는 함수
t_tree_node	*insert_rdr_node(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_token	*value;
	t_tokenize	*token;
	t_tree_node	*new_node;

	token = ((t_list *)(dque->pop_front(dque)))->content;
	value = make_value(tk_list, token, dque);
	new_node = create_node(value);
	insert(cur_node, LEFT, new_node);
	return (new_node);
}
// s_cmd노드를 만들어서 insert하는 함수
t_tree_node *insert_s_cmd_node(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_token	*value;
	t_tokenize	*token;
	t_tree_node	*new_node;

	// set_simple_cmd() first;
}
void	insert_root(t_tree *tree)
{
	t_tree_node	*root;
	t_token		*value;

	value = ft_malloc(sizeof(t_token));
	value->type = PIPE;
	value->cmd_val.pipe->fd[0] = 0;
	value->cmd_val.pipe->fd[1] = 0;
	root = create_node(value);
	tree->root = root;
}

void	save_dque(t_list *tk_list, t_list *cur_list, t_deque *dque)
{
	if (!dque)
		deque_init(ft_lstsize(tk_list));
	if (((t_tokenize *)cur_list->content)->type == PIPE || !cur_list)
	{
		if (((t_tokenize *)cur_list->content)->type == PIPE)
			dque->push_front(dque, cur_list);
		return ;
	}
	dque->push_rear(dque, cur_list);
	cur_list = cur_list->next;
	save_dque(tk_list, cur_list, dque);
	return ;
}
// dque를 받아서 처리하는 방식으로 수정핋요.
t_token	*make_value(t_list *tk_list, t_tokenize *token, t_deque *dque)
{
	t_token	*value;

	value = malloc(sizeof(t_token));
	ft_bzero(value, sizeof(value));
	if (!token || token->type == PIPE)
		set_pipe(tk_list, token, value);
	else if (token->type == RDR)
		set_rdr(tk_list, dque, token, value);
	else if (token->type == WORD)
		set_simple_cmd(tk_list, dque, token, value); // 여기에 들어오면 첫번째는 cmd, 나머지는 args
	return (value);
}
// 인자로 받는 tk_list는 트리에 넣을 해당 노드이다.
void	set_rdr(t_list *tk_list, t_deque *dque, t_tokenize *token , t_token *value)
{
	t_list		*next_list;
	t_tokenize	*next_token;

	next_list = NULL;
	next_token = NULL;
	if (token->str == '<')
		value->cmd_val.rdr->rdr_type = IN;
	else if (token->str == '>')
		value->cmd_val.rdr->rdr_type = OUT;
	else if (token->str == '>>')
		value->cmd_val.rdr->rdr_type = APPEND;
	else if (token->str == '<<')
		value->cmd_val.rdr->rdr_type = HEREDOC;
	delete_lst_node(tk_list, token);
	if (((t_tokenize *)((t_list *)(dque->nodes[dque->front])))->type == WORD)
	{
		next_list = dque->pop_front(dque);
		next_token = next_list->content;
		if (next_token->type == WORD)
		{
			value->cmd_val.rdr->file = ft_strdup(next_token->str);
			delete_lst_node(tk_list, next_token);
			return ;
		}
	}
	dque->push_front(dque, next_list);
	value->cmd_val.rdr->file = NULL;
}

void	set_pipe(t_list *tk_list, t_tokenize *token , t_token *value)
{
	value->type = PIPE;
	value->cmd_val.pipe->fd[0] = 0;
	value->cmd_val.pipe->fd[1] = 0;
	if (token)
		delete_lst_node(tk_list, token);
}
// cmd->args 에는 cmd도 들어가야한다.
void	set_simple_cmd(t_list *tk_list, t_deque *dque, t_tokenize *token, t_token *value)
{
	t_tokenize	*tmp;

	value->type = S_CMD;
	value->cmd_val.simple_cmd->cmd = ft_strdup(token->str);
	delete_lst_node(tk_list, token);
	while (dque->use_size != 0)
	{
		value->cmd_val.simple_cmd->args = ft_malloc(sizeof(char *) * (dque->use_size + 1));
		value->cmd_val.simple_cmd->args[dque->use_size] = NULL;
		token = ((t_list *)(dque->pop_rear))->content;
		value->cmd_val.simple_cmd->args[dque->use_size] = ft_strdup(token->str);
	}
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
