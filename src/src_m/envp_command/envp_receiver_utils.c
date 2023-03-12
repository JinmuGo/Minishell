/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_receiver_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:45:27 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 14:54:16 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"

void	free_bucket(t_hash_table *ht)
{
	int	i;

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

t_bool	hash_put(t_hash_elem *elem, const char *key, const char *val)
{
	const t_bool	is_same = is_same_key(elem->key, key);

	if (elem->val == NULL && !is_same)
	{
		elem->key = (char *)key;
		elem->val = (char *)val;
		elem->val_len = ft_strlen(val);
		return (FT_TRUE);
	}
	else if (is_same)
	{
		free(elem->key);
		if (elem->val)
			free(elem->val);
		elem->key = (char *)key;
		elem->val = (char *)val;
		elem->val_len = ft_strlen(val);
		return (FT_TRUE);
	}
	return (FT_FALSE);
}

t_bool	is_same_key(const char *origin, const char *judge)
{
	if (ft_strcmp(origin, judge))
		return (FT_FALSE);
	else
		return (FT_TRUE);
}

t_hash_asset	hash_asset_init(t_hash_table *ht, const char *str)
{
	const int		key = ft_add_all_ascii(str);
	const int		hash = key % ht->size;
	const int		d_hash = ht->prime - (key % ht->prime);
	t_hash_asset	rv;

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

void	hash_resize(t_hash_table *ht)
{
	const t_hash_elem	*old_bucket = ht->bucket;
	const int			old_size = ht->size;
	t_hash_asset		asset;
	int					idx;
	int					i;

	ht->size = ft_find_prev_prime(ht->size * H_GROWTH_FACTOR);
	ht->bucket = ft_calloc(ht->size, sizeof(t_hash_elem));
	ht->prime = ft_find_prev_prime(ht->size);
	ht->cnt = 0;
	i = -1;
	while (++i < old_size)
	{
		if (old_bucket[i].val != NULL)
		{
			asset = hash_asset_init(ht, old_bucket[i].key);
			idx = (asset.hash + i * asset.d_hash) % ht->size;
			if (hash_put(\
				&ht->bucket[idx], old_bucket[i].key, old_bucket[i].val))
				ht->cnt++;
		}
	}
}
