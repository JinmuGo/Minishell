/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:14:24 by jgo               #+#    #+#             */
/*   Updated: 2022/11/17 11:03:22 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_c(va_list *ap, const char conversion)
{
	const int	arg = va_arg(*ap, int);

	if (conversion != CHAR)
		return (-1);
	return (ft_putchar(arg));
}
