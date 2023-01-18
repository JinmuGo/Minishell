/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:46:00 by jgo               #+#    #+#             */
/*   Updated: 2022/11/23 14:32:46 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_d(va_list *ap, const char conversion)
{
	const int	arg = va_arg(*ap, int);
	const char	*str = ft_itoa_base(arg, "0123456789");
	int			iter;

	if (str && (conversion == DECIMAL || conversion == INT))
	{
		iter = ft_putstr((char *)str);
		free((void *)str);
		return (iter);
	}
	return (-1);
}
