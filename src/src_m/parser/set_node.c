/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:43:01 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:43 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "data_structure.h"

t_token	*make_value(t_list **tk_list, t_tokenize *token, t_deque *dque)
{
	t_token	*value;

	value = ft_calloc(1, sizeof(t_token));
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
		set_simple_cmd(tk_list, dque, token, value);
	}
	return (value);
}

void	set_rdr(
	t_list **tk_list, t_deque *dque, t_tokenize *token, t_token *value)
{
	if (!ft_strncmp(token->str, "<", 2))
		value->cmd_val.rdr->rdr_type = IN;
	else if (!ft_strncmp(token->str, ">", 2))
		value->cmd_val.rdr->rdr_type = OUT;
	else if (!ft_strncmp(token->str, ">>", 3))
		value->cmd_val.rdr->rdr_type = APPEND;
	else if (!ft_strncmp(token->str, "<<", 3))
	{
		value->cmd_val.rdr->rdr_type = HEREDOC;
		here_doc(tk_list, dque, value);
		*tk_list = delete_lst_node(tk_list, token);
		return ;
	}
	*tk_list = delete_lst_node(tk_list, token);
	if (((t_tokenize *)(((t_list *)
				(dque->nodes[dque->front]))->content))->type == WORD)
	{
		set_rdr_file(tk_list, dque, value);
		return ;
	}
	value->cmd_val.rdr->file = NULL;
}

void	set_rdr_file(t_list **tk_list, t_deque *dque, t_token *value)
{
	t_list		*next_list;
	t_tokenize	*next_token;

	next_list = NULL;
	next_token = NULL;
	next_list = dque->pop_front(dque);
	next_token = next_list->content;
	value->cmd_val.rdr->file = ft_strdup(next_token->str);
	*tk_list = delete_lst_node(tk_list, next_token);
}

void	set_pipe(t_list **tk_list, t_tokenize *token, t_token *value)
{
	value->type = PIPE;
	value->cmd_val.pipe->fd[0] = 0;
	value->cmd_val.pipe->fd[1] = 0;
	if (token)
		*tk_list = delete_lst_node(tk_list, token);
}

void	set_simple_cmd(
	t_list **tk_list, t_deque *dque, t_tokenize *token, t_token *value)
{
	value->type = S_CMD;
	value->cmd_val.simple_cmd->cmd = ft_strdup(token->str);
	value->cmd_val.simple_cmd->args = NULL;
	*tk_list = delete_lst_node(tk_list, token);
	if (dque->use_size > 0)
	{
		value->cmd_val.simple_cmd->args \
			= ft_malloc(sizeof(char *) * (dque->use_size + 2));
		value->cmd_val.simple_cmd->args[0] \
			= ft_strdup(value->cmd_val.simple_cmd->cmd);
		value->cmd_val.simple_cmd->args[dque->use_size + 1] = NULL;
		while (dque->use_size != 0)
		{
			token = ((t_list *)(dque->pop_rear(dque)))->content;
			((t_simple_cmd *)
			value->cmd_val.simple_cmd)->args[dque->use_size + 1] \
				= ft_strdup(token->str);
			*tk_list = delete_lst_node(tk_list, token);
		}
		return ;
	}
	value->cmd_val.simple_cmd->args = ft_malloc(sizeof(char *) * 2);
	value->cmd_val.simple_cmd->args[0] \
		= ft_strdup(value->cmd_val.simple_cmd->cmd);
	value->cmd_val.simple_cmd->args[1] = NULL;
}
