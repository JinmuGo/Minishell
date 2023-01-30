/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:53:21 by jgo               #+#    #+#             */
/*   Updated: 2023/01/30 21:35:19 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"

int main(int argc, char **argv, char **envp)
{
	t_tree  *tree;

	// ft_bzero(get_meta(), sizeof(t_meta));
	// signal(SIGQUIT, signal_process);
	// signal(SIGINT, signal_process);
	// envp_init(envp);
	// prompt();
	tokenizer();
	
	return (EXIT_SUCCESS);
}