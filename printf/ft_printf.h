/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 09:47:52 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/08 21:44:16 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>

# define STD_OUT		1

# define TYPE_CHAR		1
# define TYPE_STRING	2
# define TYPE_POINT		3
# define TYPE_DECADE	4
# define TYPE_INT		5
# define TYPE_U_DECADE	6
# define TYPE_S_HEX		7
# define TYPE_L_HEX		8
# define TYPE_AMPERSAND	9

# define MIN_INT		-2147483648
# define MAX_INT		2147483647

typedef struct  s_data
{
    short	flg_zero;
	short	flg_hypen;
	short	flg_width;
	short	flg_precision;
    size_t	leng_width;
    size_t	leng_precision;
    short	type;
}               t_data;

int		ft_printf(const char *format, ...);
void	pf_print_num(unsigned int n, int fd);
size_t	pf_cnt_int(int n, t_data data);
size_t	pf_put_int(int n, t_data data, int fd);
size_t	print_int(va_list ap, t_data data);

size_t	repeat_char(char c, size_t from, size_t until);
size_t	find_len_zero(long long num, t_data data, int degree);
size_t	pf_cnt_digit(long long num, t_data data, int degree);

size_t	pf_putnstr_fd(char *s, size_t n, int fd);
size_t  print_char(va_list ap, t_data data);
size_t  print_string(va_list ap, t_data data);

size_t	print_unsigned_int(va_list ap, t_data data);

size_t	print_hex(va_list ap, t_data data);

size_t	cnt_digit_p(unsigned long long num, t_data data, int degree);
size_t	len_zero_p(unsigned long long num, t_data data, int degree);

size_t	print_point(va_list ap, t_data data);

size_t	print_ampersand(t_data data);
#endif