/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:53:00 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/09 11:46:51 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_p(unsigned long long n, int fd)
{
	if (n < 16)
		write(fd, &("0123456789abcdef"[n % 16]), sizeof(char));
	else
	{
		print_p(n / 16, fd);
		write(fd, &("0123456789abcdef"[n % 16]), sizeof(char));
	}
}

size_t	cnt_p(unsigned long long n, t_data data)
{
	return (len_zero_p(n, data, 16) + cnt_digit_p(n, data, 16));
}

size_t	put_p(unsigned long long n, t_data data, int fd)
{
	size_t len_zero;
	size_t cnt_zero;

	cnt_zero = 0;
	len_zero = len_zero_p(n, data, 16);
	if (n == 0)
	{
		ft_putstr_fd("0x", STD_OUT);
		if (!(data.flg_precision == 1 && data.leng_precision == 0))
			ft_putchar_fd('0', STD_OUT);
		repeat_char('0', cnt_zero, len_zero);
	}
	else
	{
		ft_putstr_fd("0x", STD_OUT);
		repeat_char('0', cnt_zero, len_zero);
		print_p(n, fd);
	}
	return (len_zero + cnt_digit_p(n, data, 16));
}

size_t	print_point(va_list ap, t_data data)
{
	unsigned long long	p;
	size_t				len_prted;

	p = va_arg(ap, unsigned long long);
	if (data.flg_hypen == 0)
	{
		len_prted = cnt_p(p, data) + 2;
		len_prted += repeat_char(' ', len_prted, data.leng_width);
		put_p(p, data, STD_OUT);
	}
	else
	{
		len_prted = put_p(p, data, STD_OUT) + 2;
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	return (len_prted);
}
