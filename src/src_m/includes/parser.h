/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:06:12 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/03 17:42:32 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* tokenize.c */

t_list		*tokenize(char *line);
void		make_tk_list(t_list *tk_list, char *line, int size);
int			make_word(t_list *tk_list, char *line, t_tokenize *token, t_stack *qte);
int			token_node_add(t_list *tk_list, char *line, t_tokenize *token);
t_tokenize	*tokenize_init(t_tokenize *token, t_token_type type);
void		in_quote(char *line, t_tokenize *token, t_stack *qte);

void		print_tokenize(t_list *tk_list);
#endif
