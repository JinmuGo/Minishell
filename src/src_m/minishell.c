/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:53:21 by jgo               #+#    #+#             */
/*   Updated: 2023/02/02 15:38:46 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "stack.h"

int main(int argc, char **argv, char **envp)
{
	t_tree  *tree;

	// ft_bzero(get_meta(), sizeof(t_meta));
	signal(SIGQUIT, signal_process);
	signal(SIGINT, signal_process);
	// envp_init(envp);
	prompt();
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}
