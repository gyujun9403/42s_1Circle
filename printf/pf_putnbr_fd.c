/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygj <ygj@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:44:41 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/07 23:54:51 by ygj              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t		pf_cnt_digit(int num, int degree)
{
	long	temp_num;
	size_t	digit;

	if (num == 0)
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

void	print_num(int n, int fd)
{
	if (n < 10)
		write(fd, &("0123456789"[n]), sizeof(char));
	else
	{
		print_num(n / 10, fd);
		write(fd, &("0123456789"[n % 10]), sizeof(char));
	}
}

size_t	find_len_zero(int n, int precision, int degree)
{
	size_t digit;

	digit = pf_cnt_digit(n, degree);
	if (n < 0)
		if (digit < precision + 1)
			return (precision + 1 - digit);
	else
		if (digit < precision)
			return (precision - digit);
	return (0);
}

void	pf_putnbr_fd(int n, int precision, int fd)
{
	size_t len_zero;
	size_t cnt_zero;

	cnt_zero = 0;
	len_zero = find_len_zero(n, precision, 10);
	if (n == -2147483648)
		{
			write(fd, "-", sizeof(char));
			while (cnt_zero < len_zero)
				write(fd, "0", sizeof(char));
			write(fd, "2147483648", sizeof(char) * 10);
		}
	else if (n < 0)
	{
		write(fd, "-", sizeof(char));
		while (cnt_zero < len_zero)
				write(fd, "0", sizeof(char));
		print_num(-n, fd);
	}
	else
	{
		while (cnt_zero < len_zero)
				write(fd, "0", sizeof(char));
		print_num(n, fd);
	}
}
