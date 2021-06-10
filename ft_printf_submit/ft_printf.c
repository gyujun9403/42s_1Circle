/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 09:45:43 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/09 12:55:37 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	find_type_n_print(const char **format, va_list ap, t_data *data)
{
	size_t return_value;

	return_value = 0;
	if (**format == 'c')
		return_value = print_char(ap, *data);
	else if (**format == 's')
		return_value = print_string(ap, *data);
	else if (**format == 'p')
		return_value = print_point(ap, *data);
	else if (**format == 'd')
		return_value = print_int(ap, *data);
	else if (**format == 'i')
		return_value = print_int(ap, *data);
	else if (**format == 'u')
		return_value = print_unsigned_int(ap, *data);
	else if (**format == 'x')
		return_value = print_hex(ap, *data, S_HEX);
	else if (**format == 'X')
		return_value = print_hex(ap, *data, L_HEX);
	else if (**format == '%')
		return_value = print_ampersand(*data);
	++*format;
	return (return_value);
}

void	get_asterisk(const char **format, va_list ap, t_data *data, short flg)
{
	int	temp;

	++(*format);
	temp = va_arg(ap, int);
	if (flg == IS_WIDTH)
	{
		data->flg_width = TRUE;
		if (temp < 0)
		{
			data->flg_hypen = TRUE;
			data->leng_width = -temp;
		}
		else
			data->leng_width = temp;
	}
	else
	{
		if (temp < 0)
			data->flg_precision = FALSE;
		else
			data->leng_precision = temp;
	}
}

void	get_format_nbr(const char **format, t_data *data, short flg)
{
	if (flg == IS_WIDTH)
		while (ft_isdigit(**format))
			data->leng_width = (*((*format)++) - '0') + 10 * data->leng_width;
	else
		while (ft_isdigit(**format))
			data->leng_precision = (*((*format)++) - '0')
			+ 10 * data->leng_precision;
}

size_t	check_opt(const char **format, va_list ap)
{
	t_data	data;

	ft_bzero((void *)&data, sizeof(data));
	while (**format == '0' || **format == '-')
		if (*((*format)++) == '0')
			data.flg_zero = TRUE;
		else
			data.flg_hypen = TRUE;
	if (ft_isdigit(**format))
	{
		data.flg_width = TRUE;
		get_format_nbr(format, &data, IS_WIDTH);
	}
	else if (**format == '*')
		get_asterisk(format, ap, &data, IS_WIDTH);
	if (**format == '.')
	{
		data.flg_precision = TRUE;
		++*format;
		if (ft_isdigit(**format))
			get_format_nbr(format, &data, IS_PRECISION);
		else if (**format == '*')
			get_asterisk(format, ap, &data, IS_PRECISION);
	}
	return (find_type_n_print(format, ap, &data));
}

int		ft_printf(const char *format, ...)
{
	va_list ap;
	size_t	cnt_return;

	cnt_return = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			cnt_return += check_opt(&format, ap);
		}
		else
		{
			ft_putchar_fd(*format, STD_OUT);
			++format;
			++cnt_return;
		}
	}
	return (cnt_return);
}
