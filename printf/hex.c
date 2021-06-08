/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:09:29 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/08 20:17:35 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_print_hex(unsigned int n, int fd, short type)
{
	if (type == TYPE_S_HEX)
	{
		if (n < 16)
			write(fd, &("0123456789abcdef"[n]), sizeof(char));
		else
		{
			pf_print_hex(n / 16, fd, type);
			write(fd, &("0123456789abcdef"[n % 16]), sizeof(char));
		}
	}
	else
	{
		if (n < 16)
			write(fd, &("0123456789ABCDEF"[n]), sizeof(char));
		else
		{
			pf_print_hex(n / 16, fd, type);
			write(fd, &("0123456789ABCDEF"[n % 16]), sizeof(char));
		}
	}
}

size_t	pf_cnt_hex(unsigned int n, t_data data)
{
	return (find_len_zero(n, data, 16) + pf_cnt_digit(n, data, 16));
}

size_t	pf_put_hex(unsigned int n, t_data data, int fd)
{
	size_t len_zero;
	size_t cnt_zero;

	cnt_zero = 0;
	len_zero = find_len_zero(n, data, 16);
	if (n == 0)
	{
		if (!(data.flg_precision == 1 && data.leng_precision == 0))
			write(fd, "0", sizeof(char));
		repeat_char('0', cnt_zero, len_zero);
	}
	else
	{
		repeat_char('0', cnt_zero, len_zero);
		pf_print_hex(n, fd, data.type);
	}
	return (len_zero + pf_cnt_digit(n, data, 16));
}

size_t	print_hex(va_list ap, t_data data)
{
	unsigned int	ui;
	size_t			len_prted;

	ui = va_arg(ap, unsigned int);
	if (data.flg_hypen == 0)
	{
		len_prted = pf_cnt_hex(ui, data);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
		pf_put_hex(ui, data, STD_OUT);
	}
	else
	{
		len_prted = pf_put_hex(ui, data, STD_OUT);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	return (len_prted);
}
