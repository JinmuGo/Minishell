/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:53:21 by jgo               #+#    #+#             */
/*   Updated: 2023/03/13 13:00:32 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "envp_command.h"
#include "meta_command.h"
#include "data_structure.h"
#include "error.h"

int	main(int argc, char **argv, char **envp)
{
	t_tree	tree;
	t_meta	*meta;

	(void)argv;
	if (argc != 1)
	{
		prt_err(ERR_ARGS, ERR_ARGS_NUM);
		exit(EXIT_FAILURE);
	}
	meta = get_meta();
	tree_init(&tree);
	envp_init(envp);
	prompt(meta, &tree);
	return (EXIT_SUCCESS);
}
