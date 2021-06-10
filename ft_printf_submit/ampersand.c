/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 21:27:48 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/09 09:06:35 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	len_zero_amp(t_data data)
{
	size_t digit;

	digit = 1;
	if (data.flg_zero == 1 && data.flg_hypen == 0)
	{
		if (digit < data.leng_width)
			return (data.leng_width - digit);
	}
	return (0);
}

size_t	pf_cnt_amp(t_data data)
{
	return (len_zero_amp(data) + 1);
}

size_t	pf_put_amp(t_data data)
{
	size_t len_zero;
	size_t cnt_zero;

	cnt_zero = 0;
	len_zero = len_zero_amp(data);
	repeat_char('0', cnt_zero, len_zero);
	ft_putchar_fd('%', STD_OUT);
	return (len_zero + 1);
}

size_t	print_ampersand(t_data data)
{
	size_t			len_prted;

	if (data.flg_hypen == 0)
	{
		len_prted = pf_cnt_amp(data);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
		pf_put_amp(data);
	}
	else
	{
		len_prted = pf_put_amp(data);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	return (len_prted);
}
