/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:44:41 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/08 12:18:44 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

size_t		pf_cnt_digit(int num, int degree, t_data data)
{
	long	temp_num;
	size_t	digit;

	if (num == 0 && data.flg_precision == 1 && data.leng_precision == 0)
		digit = 0;
	else if (num == 0)
		digit = 1;
	else
	{
		digit = 0;
		if (num < 0)
		{
			temp_num = (long)(-num);
			digit++;
		}
		else
			temp_num = (long)num;
		while (temp_num != 0)
		{
			digit++;
			temp_num /= degree;
		}
	}
	return (digit);
}

void	pf_print_num(int n, int fd)
{
	if (n < 10)
		write(fd, &("0123456789"[n]), sizeof(char));
	else
	{
		pf_print_num(n / 10, fd);
		write(fd, &("0123456789"[n % 10]), sizeof(char));
	}
}

size_t	find_len_zero(int n, t_data data, int degree)
{
	size_t digit;
	size_t fill;

	digit = pf_cnt_digit(n, degree, data);
	if (data.flg_zero == 1 && data.flg_hypen == 0 
		&& data.flg_precision == 0)
	{
		fill = data.leng_width;
		if (digit < fill)
			return (fill - digit);
	}
	else
	{
		fill = data.leng_precision;
		if (n < 0)
		{
			if (digit < fill + 1)
				return (fill + 1 - digit);
		}
		else
			if (digit < fill)
				return (fill - digit);
	}
	return (0);
}

size_t	pf_cntnbr_fd(int n, t_data data)
{
	return (find_len_zero(n, data, 10) + pf_cnt_digit(n, 10, data));
}
size_t	pf_putnbr_fd(int n, t_data data, int fd)
{
	size_t len_zero;
	size_t cnt_zero;

	cnt_zero = 0;
	len_zero = find_len_zero(n, data, 10);
	if (n == -2147483648)
		{
			write(fd, "-", sizeof(char));
			while (cnt_zero++ < len_zero)
				write(fd, "0", sizeof(char));
			write(fd, "2147483648", sizeof(char) * 10);
		}
	else if (n < 0)
	{
		write(fd, "-", sizeof(char));
		while (cnt_zero++ < len_zero)
				write(fd, "0", sizeof(char));
		pf_print_num(-n, fd);
	}
	else if (n == 0)
	{
		if (!(data.flg_precision == 1 && data.leng_precision == 0))
			write(fd, "0", sizeof(char));
		//else
		//	write(fd, " ", sizeof(char));
		while (cnt_zero++ < len_zero)
			write(fd, "0", sizeof(char));
	}
	else
	{
		while (cnt_zero++ < len_zero)
				write(fd, "0", sizeof(char));
		pf_print_num(n, fd);
	}
	return (len_zero + pf_cnt_digit(n, 10, data));
}
