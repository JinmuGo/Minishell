/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:28 by jgo               #+#    #+#             */
/*   Updated: 2023/01/28 15:49:55 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATION_H
# define DECLARATION_H

# define LOOP TRUE

typedef struct s_meta t_meta;

enum e_token_type
{
	REDIR = 0
	PIPE,
	CMD,
	WORD
}

enum e_redir_type
{
	IN,
	OUT,
	APPEND,
	HEREDOC
}

struct s_meta  // 모든 구조체를 담을 부모구조체
{
	int		err;
	t_list *envp;
	t_list *unlink_lst; // here_doc의 예외처리를 위한 list
	// t_history;
}

struct s_cmd
{
	char	*cmd;
	char	**args;
}

struct s_red
{
	e_redir_type redir_type;
	char	*file;
}

struct s_pip
{
	int	fd[2];
}	t_pip;

// union 활용 버전
union u_token
{
	t_cmd *cmd_type;
	t_red *red_type;
	t_pip *pip_type;
}

struct s_token
{
 e_token_type type;
 t_utoken ud;
}

struct t_tree {
	
};

#endif