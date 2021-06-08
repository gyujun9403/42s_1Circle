/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_n_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:44:41 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/08 17:28:39 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_print_num(unsigned int n, int fd)
{
	if (n < 10)
		write(fd, &("0123456789"[n]), sizeof(char));
	else
	{
		pf_print_num(n / 10, fd);
		write(fd, &("0123456789"[n % 10]), sizeof(char));
	}
}

size_t	pf_cnt_int(int n, t_data data)
{
	return (find_len_zero(n, data, 10) + pf_cnt_digit(n, data, 10));
}

size_t	pf_put_int(int n, t_data data, int fd)
{
	size_t len_zero;
	size_t cnt_zero;

	cnt_zero = 0;
	len_zero = find_len_zero(n, data, 10);
	if (n < 0)
	{
		write(fd, "-", sizeof(char));
		repeat_char('0', cnt_zero, len_zero);
		pf_print_num((unsigned int)(-n), fd);
	}
	else if (n == 0)
	{
		if (!(data.flg_precision == 1 && data.leng_precision == 0))
			write(fd, "0", sizeof(char));
		repeat_char('0', cnt_zero, len_zero);
	}
	else
	{
		repeat_char('0', cnt_zero, len_zero);
		pf_print_num((unsigned int)n, fd);
	}
	return (len_zero + pf_cnt_digit(n, data, 10));
}

size_t	print_int(va_list ap, t_data data)
{
	int		i;
	size_t	len_prted;

	i = va_arg(ap, int);
	if (data.flg_hypen == 0)
	{
		len_prted = pf_cnt_int(i, data);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
		pf_put_int(i, data, STD_OUT);
	}
	else
	{
		len_prted = pf_put_int(i, data, STD_OUT);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	return (len_prted);
}
