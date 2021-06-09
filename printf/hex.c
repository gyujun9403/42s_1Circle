/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:09:29 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/09 11:42:47 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_print_hex(unsigned int n, int fd, short type)
{
	if (type == S_HEX)
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

size_t	pf_put_hex(unsigned int n, t_data data, short type)
{
	size_t len_zero;
	size_t cnt_zero;

	cnt_zero = 0;
	len_zero = find_len_zero(n, data, 16);
	if (n == 0)
	{
		if (!(data.flg_precision == 1 && data.leng_precision == 0))
			write(STD_OUT, "0", sizeof(char));
		repeat_char('0', cnt_zero, len_zero);
	}
	else
	{
		repeat_char('0', cnt_zero, len_zero);
		pf_print_hex(n, STD_OUT, type);
	}
	return (len_zero + pf_cnt_digit(n, data, 16));
}

size_t	print_hex(va_list ap, t_data data, short type)
{
	unsigned int	ui;
	size_t			len_prted;

	ui = va_arg(ap, unsigned int);
	if (data.flg_hypen == 0)
	{
		len_prted = pf_cnt_hex(ui, data);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
		pf_put_hex(ui, data, type);
	}
	else
	{
		len_prted = pf_put_hex(ui, data, type);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	return (len_prted);
}
