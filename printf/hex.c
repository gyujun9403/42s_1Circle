/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:09:29 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/09 13:46:54 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_hex(unsigned int n, short type)
{
	if (type == S_HEX)
	{
		if (n < 16)
			write(STD_OUT, &("0123456789abcdef"[n]), sizeof(char));
		else
		{
			put_hex(n / 16, type);
			write(STD_OUT, &("0123456789abcdef"[n % 16]), sizeof(char));
		}
	}
	else
	{
		if (n < 16)
			write(STD_OUT, &("0123456789ABCDEF"[n]), sizeof(char));
		else
		{
			put_hex(n / 16, type);
			write(STD_OUT, &("0123456789ABCDEF"[n % 16]), sizeof(char));
		}
	}
}

size_t	cnt_hex(unsigned int n, t_data data)
{
	return (f_len_zero(n, data, 16) + f_digit(n, data, 16));
}

size_t	pt_put_hex(unsigned int n, t_data data, short type)
{
	size_t len_zero;
	size_t cnt_zero;

	cnt_zero = 0;
	len_zero = f_len_zero(n, data, 16);
	if (n == 0)
	{
		if (!(data.flg_precision == TRUE && data.leng_precision == FALSE))
			write(STD_OUT, "0", sizeof(char));
		repeat_char('0', cnt_zero, len_zero);
	}
	else
	{
		repeat_char('0', cnt_zero, len_zero);
		put_hex(n, type);
	}
	return (len_zero + f_digit(n, data, 16));
}

size_t	print_hex(va_list ap, t_data data, short type)
{
	unsigned int	ui;
	size_t			len_prted;

	ui = va_arg(ap, unsigned int);
	if (data.flg_hypen == FALSE)
	{
		len_prted = cnt_hex(ui, data);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
		pt_put_hex(ui, data, type);
	}
	else
	{
		len_prted = pt_put_hex(ui, data, type);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	return (len_prted);
}
