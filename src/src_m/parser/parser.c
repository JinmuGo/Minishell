/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:46:50 by jgo               #+#    #+#             */
/*   Updated: 2023/02/16 17:45:42 by sanghwal         ###   ########seoul.kr  */
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
	make_tree(tree, tk_list, NULL, NULL);
	pre_order_traversal(tree->root, print_tree_node);
	free_tk_list(&tk_list);
	return (tree);
}

void	make_tree(t_tree *tree, t_list *tk_list, t_list *cur_list, t_tree_node *cur_node)
{
	t_deque		*dque;

	if (!cur_list && tk_list)
		cur_list = tk_list;
	if (!tree->root)
		insert_root(tree);
	if (!cur_node && tree->root)
		cur_node = tree->root;
	if (!cur_node)
		return ;
	dque = save_dque(tk_list, &cur_list, NULL);
	if (dque->use_size > 0)
		dque_to_tree(tree, &tk_list, cur_node, dque);
	free(dque->nodes);
	free(dque);
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
	t_tree_node	*next_node;

	if (cur_node == tree->root)
		return ;
	// CMD 노드 만들여부 체크 && 만들어서 dque_to_tree(cur_node = CMD)
	if (((t_token *)(cur_node->value))->type == PIPE)
		next_node = make_cmd_node(tree, tk_list, cur_node, dque);
	// RDR 노드 만들여부 체크 && 만들어서 dque_to_tree(cur_node = RDR)
	else if (((t_token *)(cur_node->value))->type == CMD)
		next_node = make_rdr_node(tree, tk_list, cur_node, dque);
	else if (((t_token *)(cur_node->value))->type == RDR)
		next_node = make_rdr_node(tree, tk_list, cur_node, dque);
	if (next_node != cur_node)
		dque_to_tree(tree, tk_list, next_node, dque);
	return ;
}

void	make_right(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_tree_node	*next_node;

	if (((t_token *)(cur_node->value))->type == RDR)
		return ;
	// CMD or PIPE 만들어서 dque_to_tree(cur_node = CMD or PIPE)
	if (((t_token *)(cur_node->value))->type == PIPE)
	{
		next_node = make_pipe_node(tree, tk_list, cur_node, dque);
		if (next_node == cur_node)
			next_node = make_cmd_node(tree, tk_list, cur_node, dque);
	}
	else if (((t_token *)(cur_node->value))->type == CMD)
		next_node = make_s_cmd_node(tree, tk_list, cur_node, dque);
	if (next_node != cur_node)
		dque_to_tree(tree, tk_list, next_node, dque);
}

t_tree_node	*make_pipe_node(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list	*token;

	if (dque->use_size > 0)
	{
		token = (t_list *)(dque->pop_front(dque));
		if (((t_tokenize *)(token->content))->type == PIPE)
		{
			dque->push_front(dque, token);
			return(insert_pipe_node(tree, tk_list, cur_node, dque));
		}
		else
			dque->push_front(dque, token);
	}
	return (cur_node);
}

t_tree_node	*make_cmd_node(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list		*token;

	if (dque->use_size > 0)
	{
		token = (t_list *)(dque->pop_front(dque));
		if (((t_tokenize *)(token->content))->type == RDR || ((t_tokenize *)(token->content))->type == WORD)
		{
			dque->push_front(dque, token);
			return(insert_cmd_node(tree, tk_list, cur_node, dque));
		}
		else
			dque->push_front(dque, token);
	}
	return (cur_node);
}

t_tree_node	*make_rdr_node(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list	*token;

	if (dque->use_size > 0)
	{
		search_rdr(dque);
		token = (t_list *)(dque->pop_front(dque));
		if (((t_tokenize *)(token->content))->type == RDR)
		{
			dque->push_front(dque, token);
			return(insert_rdr_node(tree, tk_list, cur_node, dque));
		}
		else
			dque->push_front(dque, token);
	}
	return (cur_node);
}

t_tree_node	*make_s_cmd_node(t_tree *tree, t_list *tk_list, t_tree_node *cur_node, t_deque *dque)
{
	t_list	*token;

	if (dque->use_size > 0)
	{
		token = (t_list *)(dque->pop_front(dque));
		if (((t_tokenize *)(token->content))->type == WORD)
		{
			dque->push_front(dque, token);
			return(insert_s_cmd_node(tree, tk_list, cur_node, dque));
		}
		else
			dque->push_front(dque, token);
	}
	return (cur_node);
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

	token = ((t_list *)(dque->pop_front(dque)))->content;
	value = make_value(tk_list, token, dque);
	new_node = create_node(value);
	insert(cur_node, RIGHT, new_node);
	return (new_node);
}
void	insert_root(t_tree *tree)
{
	t_tree_node	*root;
	t_token		*value;

	value = ft_malloc(sizeof(t_token));
	value->cmd_val.pipe = ft_malloc(sizeof(t_pipe));
	value->type = PIPE;
	value->cmd_val.pipe->fd[0] = 0;
	value->cmd_val.pipe->fd[1] = 0;
	root = create_node(value);
	tree->root = root;
}

t_deque	*save_dque(t_list *tk_list, t_list **cur_list, t_deque *dque)
{
	if (dque == NULL)
		dque = deque_init(ft_lstsize(tk_list));
	if (!(*cur_list))
		return (dque);
	if (*cur_list && ((t_tokenize *)(*cur_list)->content)->type == PIPE)
	{
		if (((t_tokenize *)(*cur_list)->content)->type == PIPE)
			dque->push_front(dque, *cur_list);
		return (dque);
	}
	dque->push_rear(dque, *cur_list);
	*cur_list = (*cur_list)->next;
	save_dque(tk_list, cur_list, dque);
	return (dque);
}

t_token	*make_value(t_list *tk_list, t_tokenize *token, t_deque *dque)
{
	t_token	*value;

	value = malloc(sizeof(t_token));
	ft_bzero(value, sizeof(value));
	if (!token || token->type == PIPE)
	{
		value->cmd_val.pipe = ft_malloc(sizeof(t_pipe));
		set_pipe(tk_list, token, value);
	}
	else if (token->type == RDR)
	{
		value->cmd_val.rdr = ft_malloc(sizeof(t_rdr));
		set_rdr(tk_list, dque, token, value);
	}
	else if (token->type == WORD)
	{
		value->cmd_val.simple_cmd = ft_malloc(sizeof(t_simple_cmd));
		set_simple_cmd(tk_list, dque, token, value); // 여기에 들어오면 첫번째는 cmd, 나머지는 args
	}
	return (value);
}

void	set_rdr(t_list *tk_list, t_deque *dque, t_tokenize *token , t_token *value)
{
	t_list		*next_list;
	t_tokenize	*next_token;

	next_list = NULL;
	next_token = NULL;
	if (!ft_strncmp(token->str, "<", 2))
		value->cmd_val.rdr->rdr_type = IN;
	else if (!ft_strncmp(token->str, ">", 2))
		value->cmd_val.rdr->rdr_type = OUT;
	else if (!ft_strncmp(token->str, ">>", 3))
		value->cmd_val.rdr->rdr_type = APPEND;
	else if (!ft_strncmp(token->str, "<<", 3))
		value->cmd_val.rdr->rdr_type = HEREDOC;
	delete_lst_node(tk_list, token);
	if (((t_tokenize *)((t_list *)(dque->nodes[dque->front])))->type == WORD)
	{
		next_list = dque->pop_front(dque);
		next_token = next_list->content;
		value->cmd_val.rdr->file = ft_strdup(next_token->str);
		delete_lst_node(tk_list, next_token);
		return ;
	}
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

void	set_simple_cmd(t_list *tk_list, t_deque *dque, t_tokenize *token, t_token *value)
{
	t_tokenize	*tmp;

	value->type = S_CMD;
	value->cmd_val.simple_cmd->cmd = ft_strdup(token->str);
	value->cmd_val.simple_cmd->args = NULL;
	delete_lst_node(tk_list, token);
	if (dque->use_size > 0)
	{
		value->cmd_val.simple_cmd->args = ft_malloc(sizeof(char *) * (dque->use_size + 2));
		value->cmd_val.simple_cmd->args[0] = ft_strdup(value->cmd_val.simple_cmd->cmd);
		value->cmd_val.simple_cmd->args[dque->use_size + 1] = NULL;
		while (dque->use_size != 0)
		{
			token = ((t_list *)(dque->pop_rear(dque)))->content;
			((t_simple_cmd *)value->cmd_val.simple_cmd)->args[dque->use_size] = ft_strdup(token->str);
			delete_lst_node(tk_list, token);
		}
		return ;
	}
	value->cmd_val.simple_cmd->args = ft_malloc(sizeof(char *) * 2);
	value->cmd_val.simple_cmd->args[0] = ft_strdup(value->cmd_val.simple_cmd->cmd);
	value->cmd_val.simple_cmd->args[1] = NULL;
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
		if (head_tmp->next != NULL)
		{
			free_token_str(head_tmp->next->content);
			free(head_tmp->next);
		}
	}
}

void	search_rdr(t_deque *dque)
{
	t_list	*token;
	int		cnt;
	char	*token_str;
	int		token_type;
	cnt = dque->use_size;
	while (cnt > 0)
	{
		token_str = ((t_tokenize *)(t_list *)dque->nodes[dque->front])->str;
		token_type = ((t_tokenize *)(t_list *)dque->nodes[dque->front])->type;
		if (((t_tokenize *)(t_list *)dque->nodes[dque->front])->type == RDR)
			return ;
		token = dque->pop_front(dque);
		dque->push_rear(dque, token);
		cnt--;
	}
}

void	print_tree_node(t_tree_node *node)
{
	t_tree_node	*cur_node;

	if (((t_token *)(node->value))->type == RDR)
		printf("cur_node: %p\nvalue: rdr_type: %s file: %s\nleft_node: %p\nright_node: %p\n\n", cur_node, (t_rdr_type)((t_token *)(node->value))->cmd_val.rdr->rdr_type, ((t_token *)(node->value))->cmd_val.rdr->file, cur_node->left, cur_node->right);
	else if(((t_token *)(node->value))->type == PIPE)
		printf("cur_node: %p\nvalue: fd0:%d fd1:%d\nleft_node: %p\nright_node: %p\n\n", cur_node, ((t_token *)(node->value))->cmd_val.pipe->fd[0], ((t_token *)(node->value))->cmd_val.pipe->fd[1], cur_node->left, cur_node->right);
	else if(((t_token *)(node->value))->type == CMD)
		printf("cur_node: %p\nvalue: type: %s\nleft_node: %p\nright_node: %p\n\n", cur_node, ((t_token *)(node->value))->type, cur_node->left, cur_node->right);
	else if(((t_token *)(node->value))->type == S_CMD)
	{
		printf("cur_node: %p\nvalue: cmd: %s\n", cur_node, ((t_token *)(node->value))->cmd_val.simple_cmd->cmd);
		int i = 0;
		printf("values: args: ");
		while (((t_token *)(node->value))->cmd_val.simple_cmd->args[i] != 0)
			printf("%s\n", ((t_token *)(node->value))->cmd_val.simple_cmd->args[i++]);
	}
}
