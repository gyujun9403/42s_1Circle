/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:34:38 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/09 15:25:43 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	repeat_char(char c, size_t from, size_t until)
{
	size_t cnt;

	cnt = 0;
	while (from < until)
	{
		cnt++;
		from++;
		write(STD_OUT, &c, sizeof(char));
	}
	return (cnt);
}

size_t	f_digit(long long num, t_data data, int degree)
{
	long long	temp_num;
	size_t		digit;

	if (num == 0 && data.flg_precision == TRUE && data.leng_precision == FALSE)
		digit = 0;
	else if (num == 0)
		digit = 1;
	else
	{
		digit = 0;
		if (num < 0)
		{
			temp_num = (-num);
			digit++;
		}
		else
			temp_num = num;
		while (temp_num != 0)
		{
			digit++;
			temp_num /= degree;
		}
	}
	return (digit);
}

size_t	f_len_zero(long long num, t_data data, int degree)
{
	size_t digit;

	digit = f_digit(num, data, degree);
	if (data.flg_zero == TRUE && data.flg_hypen == FALSE
		&& data.flg_precision == FALSE)
	{
		if (digit < data.leng_width)
			return (data.leng_width - digit);
	}
	else
	{
		if (num < 0)
		{
			if (digit < data.leng_precision + 1)
				return (data.leng_precision + 1 - digit);
		}
		else
		{
			if (digit < data.leng_precision)
				return (data.leng_precision - digit);
		}
	}
	return (0);
}

size_t	f_digit_p(unsigned long long num, t_data data, int degree)
{
	size_t				digit;

	if (num == 0 && data.flg_precision == TRUE && data.leng_precision == FALSE)
		digit = 0;
	else if (num == 0)
		digit = 1;
	else
	{
		digit = 0;
		while (num != 0)
		{
			digit++;
			num /= degree;
		}
	}
	return (digit);
}

size_t	f_len_zero_p(unsigned long long num, t_data data, int degree)
{
	size_t digit;

	digit = f_digit_p(num, data, degree);
	if (num != 0)
	{
		if (data.flg_zero == TRUE && data.flg_hypen == FALSE
			&& data.flg_precision == FALSE)
		{
			if (digit < data.leng_width)
				return (data.leng_width - digit);
		}
		else
		{
			if (digit < data.leng_precision)
				return (data.leng_precision - digit);
		}
	}
	return (0);
}
