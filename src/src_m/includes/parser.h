/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:06:12 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/05 18:31:00 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* tokenize.c */

t_list		*tokenize(char *line);
void		make_tk_list(t_list *tk_list, char *line, int size);
int			treat_word(t_list *tk_list, char *line, t_tokenize *token, \
	t_stack *qte);
int			treat_pipe(t_list *tk_list, char *line, t_tokenize *token);
int			treat_rdr(t_list *tk_list, char *line, t_tokenize *token);
int			token_node_add(t_list *tk_list, char *line, t_tokenize *token);
t_tokenize	*tokenize_init(t_tokenize *token, t_token_type type);
void		in_quote(char *line, t_tokenize *token, t_stack *qte);
void		free_tk_list(t_list **tk_list);
void		free_token_str(t_tokenize *content);

void		print_tokenize(t_list *tk_list);
#endif
