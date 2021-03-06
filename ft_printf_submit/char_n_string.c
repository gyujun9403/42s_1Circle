/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_n_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:12:05 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/09 13:46:14 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	pf_putnstr(char *s, size_t n)
{
	size_t	index;

	index = 0;
	if (s == NULL)
		;
	else
	{
		while (*(s + index) && index < n)
			write(STD_OUT, (s + index++), sizeof(char));
	}
	return (index);
}

size_t	print_char(va_list ap, t_data data)
{
	char	c;
	size_t	len_prted;

	len_prted = 0;
	c = va_arg(ap, int);
	if (data.flg_hypen == TRUE && data.flg_width == TRUE)
	{
		ft_putchar_fd(c, STD_OUT);
		++len_prted;
		len_prted += repeat_char(' ', len_prted, data.leng_width);
	}
	else if (data.flg_hypen == FALSE && data.flg_width == TRUE)
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

size_t	print_string(va_list ap, t_data data)
{
	char	*c;
	size_t	len_prted;
	size_t	len_str;

	len_prted = 0;
	if ((c = va_arg(ap, char *)) == NULL)
		c = "(null)";
	len_str = ft_strlen(c);
	if (data.flg_precision == TRUE && data.leng_precision < len_str)
		len_str = data.leng_precision;
	if (data.leng_width > len_str)
	{
		if (data.flg_hypen == FALSE)
		{
			len_prted += repeat_char(' ', len_prted, data.leng_width - len_str);
			return (len_prted + pf_putnstr(c, len_str));
		}
		len_prted += pf_putnstr(c, len_str);
		return (len_prted + repeat_char(' ', len_prted, data.leng_width));
	}
	else
		return (pf_putnstr(c, len_str));
}
