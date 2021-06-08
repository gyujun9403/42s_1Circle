/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:34:38 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/08 21:23:26 by gyeon            ###   ########.fr       */
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

size_t		pf_cnt_digit(long long num, t_data data, int degree)
{
	long long	temp_num;
	size_t		digit;

	if (num == 0 && data.flg_precision == 1 && data.leng_precision == 0)
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

size_t	find_len_zero(long long num, t_data data, int degree)
{
	size_t digit;

	digit = pf_cnt_digit(num, data, degree);
	if (data.flg_zero == 1 && data.flg_hypen == 0 
		&& data.flg_precision == 0)
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
			if (digit < data.leng_precision)
				return (data.leng_precision - digit);
	}
	return (0);
}

size_t		cnt_digit_p(unsigned long long num, t_data data, int degree)
{
	size_t				digit;

	if (num == 0 && data.flg_precision == 1 && data.leng_precision == 0)
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

size_t	len_zero_p(unsigned long long num, t_data data, int degree)
{
	size_t digit;

	digit = cnt_digit_p(num, data, degree);
	if (num != 0)
	{
		if (data.flg_zero == 1 && data.flg_hypen == 0 
			&& data.flg_precision == 0)
		{
			if (digit < data.leng_width && data.leng_width > 12)
				return (data.leng_width - digit);
		}
		else
		{
			if (digit < data.leng_precision && data.leng_precision > 12)
				return (data.leng_precision - digit);
		}
		//if (digit < 12)
		//	return (12 - digit);
	}
	return (0);
}