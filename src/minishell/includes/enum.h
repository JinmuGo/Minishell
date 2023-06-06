/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:55:31 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 17:00:00 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

/* enum typedef */
typedef enum e_token_type		t_token_type;
typedef enum e_rdr_type			t_rdr_type;
typedef enum e_tree_edge		t_tree_edge;
typedef enum e_simple_cmd_type	t_simple_cmd_type;
typedef enum e_envp_flags		t_envp_flags;
typedef enum e_meta_flags		t_meta_flags;
typedef enum e_err_type			t_err_type;
typedef enum e_signal_flags		t_signal_flags;
typedef enum e_sequence			t_sequence;

enum e_token_type
{
	NONE = -1,
	RDR = 0,
	PIPE = 1,
	CMD = 2,
	WORD = 3,
	S_CMD = 4
};

enum e_rdr_type
{
	IN = 0,
	OUT = 1,
	APPEND = 2,
	HEREDOC = 3
};

enum	e_tree_edge
{
	LEFT = 0,
	RIGHT = 1
};

enum	e_simple_cmd_type
{
	FT_ECHO = 0,
	FT_CD = 1,
	FT_PWD = 2,
	FT_EXPORT = 3,
	FT_UNSET = 4,
	FT_ENV = 5,
	FT_EXIT = 6,
	FT_EXTERNAL = 7
};

enum	e_envp_flags
{
	SET = 0,
	GET = 1,
	DEL = 2,
	PRINT = 3,
	CHAR = 4
};

enum	e_meta_flags
{
	META = 0,
	ENVP = 1,
	UNLINK = 2,
	ERR_NUM = 3,
	PID = 4,
	EXIT_STATUS = 5,
	SET_ERR_NUM = 6,
	SET_EXIT_STATUS = 7,
	GET_CUR_DIR = 8,
	SET_CUR_DIR = 9
};

enum	e_err_type
{
	ERR_NOTHING = 0,
	ERR_QUOTE = 100,
	ERR_MULTI = 101,
	ERR_PIPE = 102,
	ERR_MULTI_PIPE = 103,
	ERR_FIRST_PIPE = 104,
	ERR_RDR_IN = 110,
	ERR_RDR_OUT = 111,
	ERR_RDR_HERE = 112,
	ERR_RDR_APPEND = 113,
	ERR_RDR_MULTI = 114,
	ERR_NL = 120,
	ERR_HEREDOC = 200,
	ERR_HD_WRITE = 201,
	ERR_HD_OPEN = 203,
	ERR_ARGS_NUM = 300
};

enum	e_signal_flags
{
	SIG_INIT = 0,
	SIG_CHILD = 1,
	SIG_HERE = 2
};

enum	e_sequence
{
	FIRST = 0,
	MIDDLE = 1,
	LAST = 2
};

#endif
