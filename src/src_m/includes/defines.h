/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:28 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 17:05:06 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "constants.h"
# include "enum.h"

/* struct typedef */

typedef struct s_meta			t_meta;
typedef struct s_tree			t_tree;
typedef struct s_stack			t_stack;
typedef struct s_deque			t_deque;
typedef struct s_tree_node		t_tree_node;
typedef struct s_cmd			t_cmd;
typedef struct s_pipe			t_pipe;
typedef struct s_rdr			t_rdr;
typedef struct s_token			t_token;
typedef struct s_simple_cmd		t_simple_cmd;
typedef struct s_tokenize		t_tokenize;
typedef struct s_here_doc		t_here_doc;
typedef struct s_executor		t_executor;
typedef struct s_child_proc		t_child_proc;

/* union typedef */

typedef union u_cmd				t_ucmd;

/* data_structure typedef */

typedef struct s_deque			t_deque;
typedef struct s_hash_table		t_hash_table;
typedef struct s_stack			t_stack;
typedef struct s_tree			t_tree;

/* hash_table typedef */

typedef struct s_hash_table		t_hash_table;
typedef struct s_hash_asset		t_hash_asset;
typedef struct s_hash_elem		t_hash_elem;

/* func_ptr typedef */

typedef int						(*t_built_in_func)(t_simple_cmd *);
typedef void					(*t_rdr_func)(t_rdr *);

struct s_meta
{
	t_err_type		err;
	t_hash_table	*envp;
	t_list			*unlink_lst;
	int				exit_status;
	char			*cur_dir;
	char			*prompt;
};

struct s_envp
{
	char	*key;
	char	*val;
	int		val_len;
};

struct s_here_doc
{
	char	*file;
	int		fd;
};

struct s_executor
{
	t_token_type	child[2];
	t_list			*child_lst;
	t_bool			built_in;
	t_bool			single;
	int				cur_fd[2];
	int				prev_fd[2];
	int				in_fd;
	int				out_fd;
};

struct s_tree_node {
	void		*value;
	t_tree_node	*left;
	t_tree_node	*right;
};

struct s_tree {
	t_tree_node	*root;
	void		(*insert)(t_tree_node*, t_tree_edge, t_tree_node*);
	void		(*pre_order_traversal)(t_tree_node *, void (*f)(t_tree_node*));
	void		(*delete_node)(t_tree_node*);
	void		(*destroy)(t_tree *);
};

struct s_deque
{
	size_t	capacity;
	size_t	front;
	size_t	rear;
	size_t	use_size;
	void	**nodes;
	void	(*push_front)(t_deque *, void *);
	void	(*push_rear)(t_deque *, void *);
	void	*(*pop_front)(t_deque *);
	void	*(*pop_rear)(t_deque *);
	void	*(*peek_front)(const t_deque *);
	void	*(*peek_rear)(const t_deque *);
};

struct s_child_proc
{
	pid_t	pid;
	char	*name;
};

union u_cmd
{
	t_simple_cmd	*simple_cmd;
	t_rdr			*rdr;
	t_pipe			*pipe;
};

struct s_token
{
	t_token_type	type;
	t_ucmd			cmd_val;
};

struct s_simple_cmd
{
	t_simple_cmd_type	type;
	char				*cmd;
	char				**args;
};

struct s_rdr
{
	t_rdr_type	rdr_type;
	char		*file;
};

struct s_stack
{
	t_list	*arr;
	int		size;
	void	(*push)(t_stack *, void *);
	void	*(*pop)(t_stack *);
	void	*(*peek)(t_stack *);
	void	(*destory)(t_stack *);
	t_bool	(*is_empty)(t_stack *);
};

struct	s_hash_table
{
	t_hash_elem	*bucket;
	int			cnt;
	int			size;
	int			prime;
};

struct s_hash_asset
{
	int	key;
	int	hash;
	int	d_hash;
};

struct s_hash_elem
{
	char	*key;
	char	*val;
	int		val_len;
};

struct s_tokenize
{
	t_token_type	type;
	char			*str;
	int				size;
};

struct s_pipe
{
	int	fd[2];
};

#endif