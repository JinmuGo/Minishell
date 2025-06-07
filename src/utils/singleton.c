/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:23:33 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:51:59 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"

static void	init_hash_table(t_hash_table *ht)
{
	ht->size = ft_find_prev_prime(H_INITIAL_SIZE);
	ht->cnt = 0;
	ht->bucket = ft_calloc(ht->size, sizeof(t_hash_elem));
	ht->prime = ft_find_prev_prime(ht->size);
}

/**
 *
 *  you will must be free when you exit process
 *  free_bucket(meta->envp);
 *  free(meta->envp);
 *  free(meta);
 * 
*/
t_meta	*singleton(void)
{
	static t_meta	*meta;

	if (meta != NULL)
		return (meta);
	meta = ft_calloc(1, sizeof(t_meta));
	meta->envp = ft_malloc(sizeof(t_hash_table));
	meta->exit_status = EXIT_SUCCESS;
	init_hash_table(meta->envp);
	meta->err = ERR_NOTHING;
	meta->unlink_lst = ft_calloc(1, sizeof(t_list));
	meta->cur_dir = redef_cur_dir(NULL);
	meta->prompt = make_prompt(NULL);
	return (meta);
}
