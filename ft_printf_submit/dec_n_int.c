/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_n_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:44:41 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/09 13:44:20 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_num(unsigned int n)
{
	if (n < 10)
		write(STD_OUT, &("0123456789"[n]), sizeof(char));
	else
	{
		put_num(n / 10);
		write(STD_OUT, &("0123456789"[n % 10]), sizeof(char));
	}
}

size_t	pf_cnt_int(int n, t_data data)
{
	return (f_len_zero(n, data, 10) + f_digit(n, data, 10));
}

size_t	pf_put_int(int n, t_data data)
{
	size_t len_zero;
	size_t cnt_zero;

	cnt_zero = 0;
	len_zero = f_len_zero(n, data, 10);
	if (n < 0)
	{
		write(STD_OUT, "-", sizeof(char));
		repeat_char('0', cnt_zero, len_zero);
		put_num((unsigned int)(-n));
	}
	else if (n == 0)
	{
		if (!(data.flg_precision == TRUE && data.leng_precision == FALSE))
			write(STD_OUT, "0", sizeof(char));
		repeat_char('0', cnt_zero, len_zero);
	}
	else
	{
		repeat_char('0', cnt_zero, len_zero);
		put_num((unsigned int)n);
	}
	return (len_zero + f_digit(n, data, 10));
}

size_t	print_int(va_list ap, t_data data)
{
	int		i;
	size_t	len_prted;

	i = va_arg(ap, int);
	if (data.flg_hypen == FALSE)
	{
		len_prted = pf_cnt_int(i, data);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
		pf_put_int(i, data);
	}
	else
	{
		len_prted = pf_put_int(i, data);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	return (len_prted);
}
