/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:08 by jgo               #+#    #+#             */
/*   Updated: 2023/03/10 17:49:15 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

/* expander.c */
void    expander(t_tree *tree);

/* expander_utils.c */

/* shell_parameter_expansion.c */
char *shell_param_expand(char *str);

/* quote_removal.c */
char *quote_removal(char *str);

/* shell_parameter_expansion_utils.c */

void	quote_control(const t_deque *deque, char c);
t_bool is_shell_var(char c);

/* here_doc_expansino.c */
char *here_doc_expand(char *str);

/* expander_utis.c */
void	double_dollar(char *dst, char *str, int *i, int *j);
int	expand_and_dup(char *dst, char *key, int j);
int	try_expand_and_cal_len(char *str, int i, int tmp);

#endif