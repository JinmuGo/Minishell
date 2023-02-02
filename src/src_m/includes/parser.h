/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:06:12 by sanghwal          #+#    #+#             */
/*   Updated: 2023/02/02 16:55:21 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* tokenize.c */

t_list		*tokenize(char *line);
void		make_tk_list(t_list *tk_list, char *line);
void		make_word(t_list *tk_list, char *line, t_tokenize *token);
void		token_node_add(t_list *tk_list, char *line, t_tokenize *token);
t_tokenize	*tokenize_init(t_tokenize *token, t_token_type type);
void		print_tokenize(t_tokenize *token);
#endif