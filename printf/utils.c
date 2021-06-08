/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:34:38 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/08 15:45:56 by gyeon            ###   ########.fr       */
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