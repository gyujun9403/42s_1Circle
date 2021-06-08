/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 09:47:52 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/08 12:15:50 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>

# define STD_OUT		1

# define TYPE_CHAR      1
# define TYPE_STRING    2
# define TYPE_POINT     3
# define TYPE_DECADE    4
# define TYPE_INT       5
# define TYPE_U_DECADE  6
# define TYPE_S_HEX     7
# define TYPE_L_HEX     8

# define MIN_INT		-2147483648
# define MAX_INT		2147483647

//%[flags] [width] [.precision] [크기] 유형
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

int ft_printf(const char *format, ...);
size_t		pf_cnt_digit(int num, int degree, t_data data);
size_t	pf_cntnbr_fd(int n, t_data data);
size_t	pf_putnbr_fd(int n, t_data data, int fd);

#endif