/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:26 by jgo               #+#    #+#             */
/*   Updated: 2023/03/10 22:36:02 by jgo              ###   ########.fr       */
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

void	cmd_field_split_proc(t_simple_cmd *cmd, char **splited_cmd, const int origin_len)
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

void	cmd_field_split(t_simple_cmd *cmd)
{
	char **splited_arr;
	int	origin_len;
	int	i;
	// const char **splited_args = ft_split(cmd->args, ' ');

	splited_arr = ft_split(cmd->cmd, ' ');
	origin_len = ft_arrlen((void *)cmd->args);
	cmd_field_split_proc(cmd, splited_arr, origin_len);
	ft_free_all_arr(splited_arr);
}

// export a="a b c" ? field split어떻게 하지.
// cat a$a"c" 111$a" 111" 이거 field split을 shell param -> field -> quote removal
// 이렇게 해야 할 것 같은데?
// ft_split을 minishell용 split으로 따로 빼서 한 단어의 시작이 quote이면 그 단어는 split을 건너뛰어야겠다.
// field split전  quote_removal하면 안됨.
// quote_removal은 항상 마지막.
// 


// 문자열을 $와 quote를 기준으로 node를 나눈다. 
// node를 순회하면서 $의 유무를 체크한다. 
//  만약 $가 없다면
	// quote_removal만 진행한다. 
// 만약 $가 있다면
	// shell_param_expand만 진행한따.

// 
// expanding을 하고 quote_removal
t_list	*split_node(char *str, const int str_len)
{
	t_list	*lst;
	int		i;
	int		len;
    char quote;

	i = -1;
	len = 0;
	lst = NULL;
    quote = 0;
	while (++i <= str_len)
	{
        if ((str[i] == '\'' || str[i] == '\"' || str[i] == '$' || str[i] == '\0') && quote == 0)
        {
            ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i - len, len)));
            len = 0;
        }
        if (str[i] == '\'' || str[i] == '\"')
            quote = is_same_quote(quote, str[i], &len, 0);
        len++;
	}
	if (lst)
		return (lst);
	else
		return (NULL);
}


void	arg_expand(t_simple_cmd *cmd, char *str, int idx)
{
	t_list	*lst;
	t_list	*begin;
	char	*tmp;
	char	*rv;
	
	lst = split_node(str, ft_strlen(str));
	begin = lst;
	rv = ft_strdup("\0");
	if (lst == NULL)
		return ;
	while (lst)
	{
		tmp = ft_strdup(lst->content);
		lst->content = shell_param_expand(lst->content);
		if (ft_strcmp(lst->content, tmp) == 0 || is_in_quote(tmp))
			lst->content = quote_removal(lst->content);
		free(tmp);
		tmp = rv;
		rv = ft_strjoin(tmp, lst->content);
		free(tmp);
		lst = lst->next;
	}
	ft_lstclear(&begin, free);
	free(cmd->args[idx]);
	cmd->args[idx] = rv;
}

void	arg_field_split_proc(t_simple_cmd *cmd, char **splited_cmd, const int origin_len)
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

void	arg_field_split(t_simple_cmd *cmd, char *str, int cur_idx)
{
	const int	origin_len = ft_arrlen((void *)cmd->args);
	char **tmp;
	char	**args;
	int		i;
	int	len;
	int	idx;
	int	j;

	tmp = ft_split(str, ' ');
	if (*tmp == NULL)
	{
		ft_free_all_arr(tmp);
		return ;
	}
	len = ft_arrlen((void *)tmp);
	args = ft_malloc(sizeof(char *) * (len + origin_len));
	i = -1;
	idx = 0;
	while (++i < cur_idx)
		args[idx++] = ft_strdup(cmd->args[i]);
	j = -1;
	while (tmp[++j])
		args[idx++] = ft_strdup(tmp[j]);
	while (cmd->args[++i])
		args[idx++] = ft_strdup(cmd->args[i]);
	ft_free_all_arr(cmd->args);
	ft_free_all_arr(tmp);
	args[idx] = NULL;
	cmd->args = args;
}

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
	cmd_field_split(cmd);
	i = 0;
	//  export a="a b c"
	//  cat a$b"c"  aas
	while (cmd->args[++i])
	{
		if (ft_strchr(cmd->args[i], DOLLAR))
		{
			arg_expand(cmd, cmd->args[i], i);
			arg_field_split(cmd, cmd->args[i], i);
		}
		else
			arg_expand(cmd, cmd->args[i], i);
	}
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