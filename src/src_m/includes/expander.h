/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:08 by jgo               #+#    #+#             */
/*   Updated: 2023/02/18 20:48:51 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

/* expander_utils.c */

/* shell_parameter_expansion.c */
char *shell_param_expand(char *str);

/* quote_removal.c */
char *quote_removal(char *str);

/* shell_parameter_expansion_utils.c */

void	quote_control(const t_deque *deque, char c);
t_bool is_shell_var(char c);

#endif