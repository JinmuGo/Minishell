/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:46:05 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/02 18:30:19 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "data_structure.h"
#include "meta_command.h"

t_list	*delete_lst_node(t_list **tk_list, t_tokenize *token)
{
	t_list	*del_node;
	t_list	*pre_node;

	if ((*tk_list)->content == token)
	{
		del_node = *tk_list;
		*tk_list = (*tk_list)->next;
		free_token_str(del_node->content);
		free(del_node);
		del_node = NULL;
	}
	else
	{
		pre_node = *tk_list;
		while (pre_node->next->content != token)
			pre_node = pre_node->next;
		del_node = pre_node->next;
		pre_node->next = del_node->next;
		free_token_str(del_node->content);
		free(del_node);
		del_node = NULL;
	}
	return (*tk_list);
}

int	search_rdr(t_deque *dque)
{
	t_list	*token;
	int		cnt;
	int		re_cnt;

	cnt = dque->use_size;
	re_cnt = 0;
	while (cnt > 0)
	{
		if (((t_tokenize *)(((t_list *)(dque->nodes[dque->front]))->content))->type == RDR)
			return (re_cnt);
		token = dque->pop_front(dque);
		dque->push_rear(dque, token);
		cnt--;
		re_cnt++;
	}
	return (0);
}

void	recover_dque(t_deque *dque, int re_cnt)
{
	t_list	*token;

	while (re_cnt > 0)
	{
		token = dque->pop_rear(dque);
		dque->push_front(dque, token);
		re_cnt--;
	}
}

void	print_tree_node(t_tree_node *node, int level)
{
	if (node == NULL)
		return ;
	printf("%*s", level * 4, "|");
	if (((t_token *)(node->value))->type == RDR)
		printf("_RDR_node_\nrdr_type: %u, file: %s", (t_rdr_type)(((t_token *)(node->value))->cmd_val.rdr->rdr_type), ((t_token *)(node->value))->cmd_val.rdr->file);
	else if(((t_token *)(node->value))->type == PIPE)
		printf("_PIPE_node_\nfd[0][1]: %d, %d", ((t_token *)(node->value))->cmd_val.pipe->fd[0], ((t_token *)(node->value))->cmd_val.pipe->fd[1]);
	else if(((t_token *)(node->value))->type == CMD)
		printf("_CMD_node_\n ");
	else if(((t_token *)(node->value))->type == S_CMD)
	{
		printf("_S_CMD_node_\ncmd: %s, ",((t_token *)(node->value))->cmd_val.simple_cmd->cmd);
		int i = 0;
		printf("args: ");
		while (((t_token *)(node->value))->cmd_val.simple_cmd->args[i] != 0)
			printf("%s,", ((t_token *)(node->value))->cmd_val.simple_cmd->args[i++]);
	}
	printf("\n");
	print_tree_node(node->left, level + 1);
	print_tree_node(node->right, level + 1);
}

void	free_parser_node(t_tree_node *node)
{
	t_token	*token;

	token = node->value;
	if (token->type == RDR)
	{
		free(token->cmd_val.rdr->file);
		free(token->cmd_val.rdr);
	}
	else if (token->type == S_CMD)
	{
		free(token->cmd_val.simple_cmd->cmd);
		ft_free_all_arr(token->cmd_val.simple_cmd->args);
		free(token->cmd_val.simple_cmd);
	}
	else if (token->type == PIPE)
		free(token->cmd_val.pipe);
}

void	close_unlink_list(void *content)
{
	t_here_doc	*heredoc;

	if (content)
	{
		heredoc = content;
		free(heredoc->file);
		close(heredoc->fd);
		free(heredoc);
		heredoc = NULL;
	}
}
