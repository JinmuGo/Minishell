/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:26 by jgo               #+#    #+#             */
/*   Updated: 2023/03/07 20:53:49 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

void	rdr_expander(t_rdr	*rdr)
{
	if (rdr == NULL)
		return ;
	if (rdr->rdr_type != HEREDOC)
	{
		rdr->file = shell_param_expand(rdr->file);
		rdr->file = quote_removal(rdr->file);
	}
}

// void	cmd_field_split(t_simple_cmd *cmd)
// {
// 	char **split_arr;
// 	int	len;
// 	char **args;
// 	int	i;

// 	split_arr = ft_split(cmd->cmd, ' '); // 1
// 	if (split_arr == NULL)
// 		return ;
// 	free(cmd->cmd);
// 	len = ft_arrlen((void **)split_arr);
// 	args = ft_malloc(sizeof(char *) * (len + ft_arrlen((void **)cmd->args) + 1)); // 4
// 	cmd->cmd = ft_strdup(split_arr[0]);
// 	i = -1;
// 	while (split_arr[++i])
// 		args[i] = ft_strdup(split_arr[i]);
// 	i = -1;
// 	while (cmd->args[++i])
// 		args[len + i] = ft_strdup(cmd->args[i]);
// 	args[len + i] = NULL;
// 	ft_free_all_arr(cmd->args);
// 	cmd->args = args;
// 	ft_free_all_arr(split_arr);
// }

// int	args_field_split(t_simple_cmd *cmd, int	idx)
// {
// 	char **split_arr;
// 	char **args;
// 	int	len;
// 	int	i;
// 	int	j;

// 	split_arr = ft_split(cmd->args[idx], ' ');
// 	if (split_arr == NULL)
// 		return (0);
// 	len = ft_arrlen((void *)split_arr);
// 	args = ft_malloc(sizeof(char *) * (len + ft_arrlen((void **)cmd->args)));
// 	args[0] = ft_strdup(cmd->args[0]);
// 	i = 0;
// 	while(++i < idx)
// 		args[i] = ft_strdup(cmd->args[i]);
// 	j = i;
// 	while (*split_arr)
// 	{
// 		args[i++] = ft_strdup(*split_arr);
// 		split_arr++;
// 	}
// 	while (cmd->args[j])
// 		args[i++] = ft_strdup(cmd->args[j++]);
// 	args[i] = NULL;
// 	if (cmd->args)
// 	ft_free_all_arr(cmd->args);
// 	cmd->args = args;
// 	ft_free_all_arr(split_arr - len);
// 	return (len - 2);
// }

// cmd->cmd 는 split을하고 맨 처음만 살리고 뒤에는 버린다. 
// cmd->args는 split을 하고 모두 살린다.
void	field_split(t_simple_cmd *cmd)
{
	
}

void	cmd_expander(t_simple_cmd	*cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	cmd->cmd = shell_param_expand(cmd->cmd);
	cmd->cmd = quote_removal(cmd->cmd);
	i = 0;
	while (cmd->args[i])
	{
		cmd->args[i] = shell_param_expand(cmd->args[i]);
		cmd->args[i] = quote_removal(cmd->args[i]);
		i++;
	}
}

/**
 * @brief 
 * 
 * @param token 
 */
void	expander_classify_token(t_tree_node	*node)
{
	const t_token *token = (t_token *)(node->value);

	if (token == NULL)
		return ;
	// RDR OR S_CMD만 확장한다.
	if (token->type == RDR)
		rdr_expander(token->cmd_val.rdr); // 모든 rdr을 확장한다.
	else if (token->type == S_CMD)
		cmd_expander(token->cmd_val.simple_cmd);
}

// executor 에서 tree를 받으면서 실행한다.
// 그리고 만약 노드의 타입이 CMD일 경우 expanding을 진행한다.
// expander에서 node의 값이 null이 아닐 때만 확장한다.

// 1. shell parameter expansion
// 2. Quote Removal
/**
 * @brief 
 * 
 * @param node // 트리안의 모든 노드를 돈다.
 */
void    expander(t_tree *tree)
{
	if (tree == NULL || tree->root == NULL)
		return ;
	tree->pre_order_traversal(tree->root, expander_classify_token);
}

// cmd가 $로시작한다면 맨챂에있는 단어가 cmd가되고 이후의 것들은 args로 들어간다. 
//  args를 expand할 때 $가 있다면 args로 만들어준다.