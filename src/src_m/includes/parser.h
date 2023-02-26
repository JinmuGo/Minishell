/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:06:12 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/26 15:06:26 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* tokenize.c */

t_list		*tokenize(char *line);
void		make_tk_list(t_list **tk_list, char *line, int size);
int			treat_word(t_list **tk_list, char *line, t_tokenize *token, \
	t_stack *qte);
int			treat_pipe(t_list **tk_list, char *line, t_tokenize *token);
int			treat_rdr(t_list **tk_list, char *line, t_tokenize *token);
int			token_node_add(t_list **tk_list, char *line, t_tokenize *token);
t_tokenize	*tokenize_init(t_tokenize *token, t_token_type type);
void		in_quote(char *line, t_tokenize *token, t_stack *qte);
void		free_tk_list(t_list **tk_list);
void		free_token_str(t_tokenize *content);

void		print_tokenize(t_list *tk_list);

/* parser.c */

t_tree		*parser(char *line);
void		make_tree(t_tree *tree, t_list **tk_list, t_list *cur_list, t_tree_node *cur_node);
void	dque_to_tree(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
void	make_left(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
void	make_right(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
t_tree_node	*make_pipe_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
t_tree_node	*make_cmd_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
t_tree_node	*make_rdr_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
t_tree_node	*make_s_cmd_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
t_tree_node	*insert_pipe_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
t_tree_node	*insert_cmd_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
t_tree_node	*insert_rdr_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
t_tree_node *insert_s_cmd_node(t_tree *tree, t_list **tk_list, t_tree_node *cur_node, t_deque *dque);
void	insert_root(t_tree *tree);
t_deque	*save_dque(t_list *tk_list, t_list **cur_list, t_deque *dque);
t_token	*make_value(t_list **tk_list, t_tokenize *token, t_deque *dque);
void	set_rdr(t_list **tk_list, t_deque *dque, t_tokenize *token , t_token *value);
void	set_pipe(t_list **tk_list, t_tokenize *token , t_token *value);
void	set_simple_cmd(t_list **tk_list, t_deque *dque, t_tokenize *token, t_token *value);
t_list	*delete_lst_node(t_list **tk_list, t_tokenize *token);
int		search_rdr(t_deque *dque);
void	recover_dque(t_deque *dque, int re_cnt);
void	print_tree_node(t_tree_node *node, int level, char *direct);
#endif
