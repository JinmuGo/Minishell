/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_receiver_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:45:27 by jgo               #+#    #+#             */
/*   Updated: 2023/02/13 14:33:54 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"

void    free_bucket(t_hash_table *ht)
{
	int i;

	i = -1;
	while (++i < ht->size)
	{
		if (ht->bucket[i].key != NULL)
		{
			free(ht->bucket[i].key);
			free(ht->bucket[i].val);
		}
	}
	free(ht->bucket);
}

t_bool  hash_put(t_hash_elem *elem, const char *key,const char *val)
{
	if (elem->val == NULL || is_same_key(elem->key, key))
	{
		elem->key = (char *)key;
		elem->val = (char *)val;
		elem->val_len = ft_strlen(val);
		return (FT_TRUE);
	}
	return(FT_FALSE);
}

t_bool  is_same_key(const char *origin, const char *judge)
{
	if (ft_strncmp(origin, judge, ft_strlen(origin)))
		return (FT_FALSE);
	else
		return (FT_TRUE);
}

t_hash_asset    hash_asset_init(t_hash_table *ht, const char *str)
{
	t_hash_asset rv;
	const int   key = ft_add_all_ascii(str);
	const int   hash = key % ht->size;
	const int   d_hash = ht->prime - (key % ht->prime);

	if (key == -1)
	{
		rv.key = -1;
		return (rv);
	}
	rv.key = key;
	rv.hash = hash;
	rv.d_hash = d_hash;
	return (rv);
}

// debug
void display(t_hash_table *ht)
{
	printf("\nelements in the hash table are \n");
	for (int i = 0; i < ht->size; i++)
		printf("\nat index %d \t key = %s value =  %s\n", i, ht->bucket[i].key,ht->bucket[i].val);

	printf("ht size : %d\n", ht->size);
	printf("ht cnt : %d\n", ht->cnt);
}