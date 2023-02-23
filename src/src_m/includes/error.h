/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:31 by jgo               #+#    #+#             */
/*   Updated: 2023/02/22 20:55:44 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

//  File name too long 255 글자기준. 

# define ERR_SYN_RDR_OUT "syntax error: near unexpected token `>'"
# define ERR_SYN_RDR_NL "syntax error: near unexpected token `newline'"
# define ERR_SYN_RDR_IN "syntax error: near unexpected token `<'"
# define ERR_SYN_RDR_PIPE "syntax error: near unexpected token `|'"
# define ERR_SYN_HERE "syntax error near unexpected token `<<'"
# define ERR_SYN_APPEND "syntax error near unexpected token `>>'"
# define ERR_SYN_QUOTE "syntax error: unclosed quote"
# define ERR_SYN_ML "syntax error: not support multi-line"

#endif