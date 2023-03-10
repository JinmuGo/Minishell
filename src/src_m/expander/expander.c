/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:26 by jgo               #+#    #+#             */
/*   Updated: 2023/03/10 10:31:49 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "expander.h"

t_bool	is_in_quote(const char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			return (FT_TRUE);
		i++;
	}
	return (FT_FALSE);
}


void	rdr_expander(t_rdr	*rdr)
{
	if (rdr == NULL)
		return ;
	if (rdr->rdr_type != HEREDOC)
	{
		rdr->file = shell_param_expand(rdr->file);
		if (rdr->file[0] != S_QUOTE || rdr->file[0] != D_QUOTE)
			return ;
		rdr->file = quote_removal(rdr->file);
	}
}

// cmd->cmd 는 split을하고 맨 처음만 살리고 뒤에는 버린다. 
// cmd->args는 split을 하고 모두 살린다.

void	cmd_field_split(t_simple_cmd *cmd, char **splited_cmd, const int origin_len)
{
	const int	len = ft_arrlen((void *)splited_cmd);
	int	i;
	char	**args;
	int	idx;

	if (*splited_cmd == NULL)
		return ;
	free(cmd->cmd);
	cmd->cmd = ft_strdup(splited_cmd[0]);
	args = ft_malloc(sizeof(char *) * (len + origin_len));
	i = -1;
	idx = 0;
	while (++i < len)
		args[idx++] = ft_strdup(splited_cmd[i]);
	i = 0;
	while (cmd->args[++i])
		args[idx++] = ft_strdup(cmd->args[i]);
	ft_free_all_arr(cmd->args);
	args[idx] = NULL;
	cmd->args = args;
}

void	args_field_split(t_simple_cmd *cmd, char **splited_arr, const int origin_len)
{
	if (splited_arr == NULL)
		return ;
	
}

void	field_split(t_simple_cmd *cmd)
{
	char **splited_arr;
	int	origin_len;
	int	i;
	// const char **splited_args = ft_split(cmd->args, ' ');

	splited_arr = ft_split(cmd->cmd, ' ');
	origin_len = ft_arrlen((void *)cmd->args);
	cmd_field_split(cmd, splited_arr, origin_len);
	ft_free_all_arr(splited_arr);
	i = -1;
	origin_len = ft_arrlen((void *)cmd->args);
	while (cmd->args[++i])
	{
		splited_arr = ft_split(cmd->args[i], ' ');	    
		args_field_split(cmd, splited_arr, origin_len);
		ft_free_all_arr(splited_arr);
	}
}

// export a="a b c" ? field split어떻게 하지.
// cat a$a"c" 111$a" 111" 이거 field split을 shell param -> field -> quote removal
// 이렇게 해야 할 것 같은데?
// ft_split을 minishell용 split으로 따로 빼서 한 단어의 시작이 quote이면 그 단어는 split을 건너뛰어야겠다.
void	cmd_expander(t_simple_cmd	*cmd)
{
	const char *dup_cmd = (const char *)ft_strdup(cmd->cmd);
	const char **dup_args = (const char **)ft_arrdup((const char **)cmd->args);
	t_bool expanded;
	int	i;

	if (cmd == NULL)
		return ;
	cmd->cmd = shell_param_expand(cmd->cmd);
	if (ft_strcmp(cmd->cmd, dup_cmd) == 0 || is_in_quote(dup_cmd))
		cmd->cmd = quote_removal(cmd->cmd);
	i = 0;
	while (cmd->args[i])
	{
		cmd->args[i] = shell_param_expand(cmd->args[i]);
		if (ft_strcmp(cmd->args[i], dup_args[i]) == 0 || is_in_quote(dup_args[i]))
			cmd->args[i] = quote_removal(cmd->args[i]);
		i++;
	}
	field_split(cmd);
	free((void *)dup_cmd);
	ft_free_all_arr((char **)dup_args);
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