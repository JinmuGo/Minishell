/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:08 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 20:24:47 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

/* expander.c */
void	expander(t_tree_node *node);

/* expander_utils.c */

/* shell_parameter_expansion.c */
char	*shell_param_expand(char *str, t_list *next);

/* quote_removal.c */
char	*quote_removal(char *str);

/* shell_parameter_expansion_utils.c */

void	quote_control(const t_deque *deque, char c);
t_bool	is_shell_var(char c);
void	adjust_param_idx(char *str, int *i);

/* here_doc_expansino.c */
char	*here_doc_expand(char *str);

/* expander_utis.c */
void	double_dollar(char *dst, char *str, int *i, int *j);
int		expand_and_dup(char *dst, char *key, int j);
int		try_expand_and_cal_len(char *str, int i, int tmp);
char	is_same_quote(char quote, char c, char initial);
t_bool	is_in_quote(const char *str);

/* ft_field_split.c */
void	cmd_field_split(t_simple_cmd *cmd, const char *dup_cmd);
void	arg_field_split(\
	t_simple_cmd *cmd, char *str, int cur_idx, const int origin_len);

/* ft_mini_strchr.c */
char	*ft_mini_strchr(const char *s, int c);
char	*ft_imin_strchr(const char *s, int c);

/* field_split_utils.c */
void	fill_arg(t_simple_cmd *cmd, char **args, char **tmp, int cur_idx);
t_list	*split_node(char *str, const int str_len);

#endif