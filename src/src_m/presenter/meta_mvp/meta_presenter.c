/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:56:59 by jgo               #+#    #+#             */
/*   Updated: 2023/02/09 20:57:01 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_meta  *get_meta(void)
{
	static t_meta *meta;

	if (meta != NULL)
		return (meta);
	meta = ft_malloc(sizeof(t_meta));
	return (meta);
}