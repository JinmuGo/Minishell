/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:08 by jgo               #+#    #+#             */
/*   Updated: 2023/02/13 14:22:44 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

char *shell_param_expand(char *str);
void    quote_removal(char *str);

/* shell_parameter_expansion_utils.c*/

t_bool is_shell_var(char c);

#endif