/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:53:00 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/09 13:43:16 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_p(unsigned long long n)
{
	if (n < 16)
		write(STD_OUT, &("0123456789abcdef"[n % 16]), sizeof(char));
	else
	{
		put_p(n / 16);
		write(STD_OUT, &("0123456789abcdef"[n % 16]), sizeof(char));
	}
}

size_t	pt_cnt_p(unsigned long long n, t_data data)
{
	return (f_len_zero_p(n, data, 16) + f_digit_p(n, data, 16));
}

size_t	pt_put_p(unsigned long long n, t_data data)
{
	size_t len_zero;
	size_t cnt_zero;

	cnt_zero = 0;
	len_zero = f_len_zero_p(n, data, 16);
	if (n == 0)
	{
		ft_putstr_fd("0x", STD_OUT);
		if (!(data.flg_precision == TRUE && data.leng_precision == FALSE))
			ft_putchar_fd('0', STD_OUT);
		repeat_char('0', cnt_zero, len_zero);
	}
	else
	{
		ft_putstr_fd("0x", STD_OUT);
		repeat_char('0', cnt_zero, len_zero);
		put_p(n);
	}
	return (len_zero + f_digit_p(n, data, 16));
}

size_t	print_point(va_list ap, t_data data)
{
	unsigned long long	p;
	size_t				len_prted;

	p = va_arg(ap, unsigned long long);
	if (data.flg_hypen == FALSE)
	{
		len_prted = pt_cnt_p(p, data) + 2;
		len_prted += repeat_char(' ', len_prted, data.leng_width);
		pt_put_p(p, data);
	}
	else
	{
		len_prted = pt_put_p(p, data) + 2;
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	return (len_prted);
}
