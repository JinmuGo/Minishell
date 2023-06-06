/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:54:24 by jgo               #+#    #+#             */
/*   Updated: 2023/03/17 16:32:15 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define LOOP TRUE
# define ROOT 0
# define MY_PROMPT " ❯ "
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define DOLLAR	 '$'
# define BUILT_IN_EXEC_OK 1
# define BUILT_IN_EXEC_FAIL 0
# define READ 0
# define WRITE 1

/* exit status */
# define EXIT_COM_NOT_FOUND 127
# define EXIT_SIGNAL_DFL 128
# define EXIT_SIGINT 130 // 128 + 2
# define EXIT_SIGQUIT 131 // 128 + 3
# define EXIT_SIGTERM 143 // 128 + 15

/* color */
# define BOLD "\e[1m"
# define MAGENTA "\e[35m"
# define CYAN "\e[36m"
# define GREEN "\e[92m"
# define GRAY "\e[90m"
# define RED "\e[91m"
# define BLUE "\e[94m"
# define RESET "\e[0m"

/* hash_table */
# define H_INITIAL_SIZE 100
# define H_GROWTH_FACTOR 2

#endif