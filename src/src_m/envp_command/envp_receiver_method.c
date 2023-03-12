/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_receiver_method.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:44:08 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:33:33 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"

t_hash_elem	*hash_get(t_hash_table *ht, const char *key)
{
	const t_hash_asset	asset = hash_asset_init(ht, key);
	int					idx;
	int					i;

	i = -1;
	while (++i < ht->size)
	{
		idx = (asset.hash + i * asset.d_hash) % ht->size;
		if (is_same_key(ht->bucket[idx].key, key))
			return (&ht->bucket[idx]);
	}
	return (NULL);
}

void	hash_insert(t_hash_table *ht, const char *key, const char *val)
{
	const t_hash_asset	asset = hash_asset_init(ht, key);
	int					idx;
	int					i;

	i = -1;
	while (++i < ht->size)
	{
		idx = (asset.hash + i * asset.d_hash) % ht->size;
		if (hash_put(&ht->bucket[idx], key, val))
		{
			ht->cnt++;
			break ;
		}
	}
	if (i == ht->size)
	{
		hash_resize(ht);
		hash_insert(ht, key, val);
	}
}

void	hash_delete(t_hash_table *ht, const char *key)
{
	t_hash_elem	*target;

	target = hash_get(ht, key);
	if (target == NULL)
		return ;
	free(target->key);
	free(target->val);
	target->key = NULL;
	target->val = NULL;
	target->val_len = 0;
}

void	hash_print_all(const char *option, t_hash_table *ht)
{
	int	i;

	i = -1;
	while (++i < ht->size)
	{
		if (ht->bucket[i].key)
		{
			if (option)
				printf(\
					"%s %s=%s\n", option, ht->bucket[i].key, ht->bucket[i].val);
			else
				printf("%s=%s\n", ht->bucket[i].key, ht->bucket[i].val);
		}
	}
}

char	**hash_convert_arr(t_hash_table *ht)
{
	char		**arr;
	int			i;
	int			j;

	arr = ft_calloc(sizeof(char *), ht->cnt + 1);
	i = 0;
	j = 0;
	while (i < ht->size)
	{
		if (ht->bucket[i].key)
			arr[j++] = ft_strcombine(\
				3, ht->bucket[i].key, "=", ht->bucket[i].val);
		i++;
	}
	return (arr);
}
