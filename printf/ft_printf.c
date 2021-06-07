/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygj <ygj@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 09:45:43 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/07 23:54:47 by ygj              ###   ########.fr       */
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

void	pf_putnstr_fd(char *s, size_t n, int fd)
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
}

void	print_int(va_list ap, t_data data)
{
	int i;
	size_t	len_empty;
	size_t	digit;
	size_t	len_prted;
	size_t	len_data;
	size_t	len_empty2;
	
	i = va_arg(ap, int);
	digit = pf_cnt_digit(i, 10);
	len_prted = 0;
	
	if (data.leng_width > digit)
		len_empty = data.leng_width - digit;
	else
		len_empty = 0;
	if (data.flg_zero == 1 && data.flg_hypen == 1)
	{
		pf_putnbr_fd(i, len_empty, STD_OUT);
	}
	else if (data.flg_zero == 1)
	{
		while (len_prted < len_empty)
		{
			len_prted++;
			ft_putchar_fd(' ', STD_OUT);
		}
		ft_putnbr_fd(i, STD_OUT);
	}
	else if (data.flg_hypen == 1)
	{
		ft_putnbr_fd(i, STD_OUT);
		while (len_prted < len_empty)
		{
			len_prted++;
			ft_putchar_fd(' ', STD_OUT);
		}
	}
	else
	{
		if (i < 0)
			len_data = (digit < data.leng_precision + 1) ? (data.leng_precision + 1) : (digit + 1);
		else
			len_data = (digit < data.leng_precision) ? (data.leng_precision) : (digit);
		len_empty2 = (data.leng_width > len_data) ? (data.leng_width - len_data) : (0);
		while (len_prted < len_empty2)
		{
			len_prted++;
			ft_putchar_fd(' ', STD_OUT);
		}
		pf_putnbr_fd(i, data.flg_precision, STD_OUT);	
	}
	
}
void    print_char(va_list ap, t_data data)
{
    char    c;
	size_t	index;

	index = 0;
	c = va_arg(ap, int);
	if (data.flg_hypen == 1 && data.flg_width == 1)
	{
		ft_putchar_fd(c, STD_OUT);
		++index;
		while (data.leng_width > index++)
			ft_putchar_fd(' ', STD_OUT);
	}
	else if (data.flg_hypen == 0 && data.flg_width == 1)
	{
		while (data.leng_width > index++ + 1)
			ft_putchar_fd(' ', STD_OUT);
		ft_putchar_fd(c, STD_OUT);
	}
	else
		ft_putchar_fd(c, STD_OUT);
}

void    print_string(va_list ap, t_data data)
{
    char 	*c;
	char	null[] = "(null)";
	size_t	index;
	size_t	len_str;
	
	index = 0;
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
			while (index++ < data.leng_width - len_str)
				ft_putchar_fd(' ', STD_OUT);
			pf_putnstr_fd(c, len_str, STD_OUT);
		}
		else
		{
			pf_putnstr_fd(c, len_str, STD_OUT);
			while (index++ < data.leng_width - len_str)
				ft_putchar_fd(' ', STD_OUT);
		}
	}
	else
		pf_putnstr_fd(c, len_str, STD_OUT);
}

void	check_opt(const char **format, va_list ap)
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
			{
				//data.flg_hypen = 1;
				//data.leng_precision = -temp;
				data.flg_precision = 0;
			}
			else
				data.leng_precision = temp;
		}
	}
	if (check_type(**format, &data))
		(++*format);
	if (data.type == TYPE_CHAR)
		print_char(ap, data);
	else if (data.type == TYPE_DECADE || data.type == TYPE_INT)
		print_int(ap, data);
	else if (data.type == TYPE_STRING)
		print_string(ap, data);
}

int     ft_printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    while (*format)
    {
        if (*format == '%')
        {
            ++format;
            check_opt(&format, ap);
        }
		else
		{
			ft_putchar_fd(*format, STD_OUT);
        	++format;
		}
    }
    return (1);
}