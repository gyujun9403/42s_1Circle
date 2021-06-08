/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 09:45:43 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/08 20:57:29 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

short    check_type(const char c, t_data *data)
{
    if (c == 'c')
        data->type = TYPE_CHAR;
    else if (c == 's')
        data->type = TYPE_STRING;
    else if (c == 'p')
        data->type = TYPE_POINT;
    else if (c == 'd')
        data->type = TYPE_DECADE;
    else if (c == 'i')
        data->type = TYPE_INT;
    else if (c == 'u')
        data->type = TYPE_U_DECADE;
    else if (c == 'x')
        data->type = TYPE_S_HEX;
    else if (c == 'X')
        data->type = TYPE_L_HEX;
    return (data->type);
}

size_t	check_opt(const char **format, va_list ap)
{
    t_data	data;
	int 	temp;

	ft_bzero((void *)&data, sizeof(data));
	while (**format == '0' || **format == '-')
	{
		if (*((*format)++) == '0')
			data.flg_zero = 1;
		else
			data.flg_hypen = 1;
	}
	if (ft_isdigit(**format))
	{
		data.flg_width = 1;
		while (ft_isdigit(**format))
			data.leng_width = (*((*format)++) - '0') + 10 * data.leng_width;
	}
	else if (**format == '*')
	{
		++(*format);
		data.flg_width = 1;
		temp = va_arg(ap, int);
		if (temp < 0)
		{
			data.flg_hypen = 1;
			data.leng_width = -temp;
		}
		else
			data.leng_width = temp;
	}
	if (**format == '.')
	{
		data.flg_precision = 1;
		++*format;
		if (ft_isdigit(**format))
			while (ft_isdigit(**format))
				data.leng_precision = (*((*format)++) - '0') + 10 * data.leng_precision;
		else if (**format == '*')
		{
			++(*format);
			temp = va_arg(ap, int);
			if (temp < 0)
				data.flg_precision = 0;
			else
				data.leng_precision = temp;
		}
	}
	if (check_type(**format, &data))
		(++*format);
	if (data.type == TYPE_CHAR)
		return (print_char(ap, data));
	else if (data.type == TYPE_DECADE || data.type == TYPE_INT)
		return (print_int(ap, data));
	else if (data.type == TYPE_STRING)
		return (print_string(ap, data));
	else if (data.type == TYPE_U_DECADE)
		return (print_unsigned_int(ap, data));
	else if (data.type == TYPE_S_HEX || data.type == TYPE_L_HEX)
		return (print_hex(ap, data));
	else if (data.type == TYPE_POINT)
		return (print_point(ap, data));
	else if (data.type == TYPE_AMPERSAND)
		;//return (print_hex(ap, data));
	return (0);
}

int     ft_printf(const char *format, ...)
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
			++cnt_return;
            cnt_return += check_opt(&format, ap);
        }
		else
		{
			ft_putchar_fd(*format, STD_OUT);
			++format;
        	++cnt_return;
		}
    }
	if (cnt_return > 0)
		--cnt_return;
    return (cnt_return);
}