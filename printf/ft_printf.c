/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 09:45:43 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/08 15:53:09 by gyeon            ###   ########.fr       */
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

size_t	pf_putnstr_fd(char *s, size_t n, int fd)
{
	size_t	index;

	index = 0;
	if (s == NULL || fd < 0)
		;
	else
	{
		while (*(s + index) && index < n)
			write(fd, (s + index++), sizeof(char));
	}
	return (index);
}

size_t	print_int(va_list ap, t_data data)
{
	int i;
	size_t	len_prted;
	
	i = va_arg(ap, int);
	if (data.flg_hypen == 0)
	{
		len_prted = pf_cntnbr_fd(i, data);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
		pf_putnbr_fd(i, data, STD_OUT);	
	}
	else
	{
		len_prted = pf_putnbr_fd(i, data, STD_OUT);
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	return (len_prted);
}
size_t    print_char(va_list ap, t_data data)
{
    char    c;
	size_t	len_prted;

	len_prted = 0;
	c = va_arg(ap, int);
	if (data.flg_hypen == 1 && data.flg_width == 1)
	{
		ft_putchar_fd(c, STD_OUT);
		++len_prted;
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	else if (data.flg_hypen == 0 && data.flg_width == 1)
	{
		len_prted += repeat_char(' ', len_prted + 1, data.leng_width);
		ft_putchar_fd(c, STD_OUT);
		len_prted++;
	}
	else
	{
		len_prted++;
		ft_putchar_fd(c, STD_OUT);
	}
	return (len_prted);
}

size_t    print_string(va_list ap, t_data data)
{
    char 	*c;
	char	null[] = "(null)";
	size_t	len_prted;
	size_t	len_str;
	
	len_prted = 0;
	c = va_arg(ap, char *);
	if (c == NULL)
		c = null;
	len_str = ft_strlen(c);
	if (data.flg_precision == 1 && data.leng_precision < len_str)
		len_str = data.leng_precision;
	if (data.leng_width > len_str)
	{
		if (data.flg_hypen == 0)
		{
			len_prted += repeat_char(' ', len_prted, data.leng_width - len_str);
			return (len_prted + pf_putnstr_fd(c, len_str, STD_OUT));
		}
		len_prted += pf_putnstr_fd(c, len_str, STD_OUT);
		return (len_prted + repeat_char(' ', len_prted, data.leng_width));
		
	}
	else
		return (pf_putnstr_fd(c, len_str, STD_OUT));
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