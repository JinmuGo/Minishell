/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:35 by jgo               #+#    #+#             */
/*   Updated: 2023/03/10 14:09:10 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* singleton.c */

t_meta	*singleton(void);

/* input.c */

void	prompt(void);

/* utils.c */
void	close_unlink_list(void *content);
char	*redef_cur_dir(char *prev_dir);
void	free_parser_node(t_tree_node *node);
void	clear_asset(char *line, t_tree *tree, t_meta *meta);

/* prompt. c*/
char	*make_prompt(char *prev_prompt);

#endif