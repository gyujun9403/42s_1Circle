/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:09:29 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/01 14:10:19 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst == src)
		;
	else
	{
		while (n-- > 0)
			*(unsigned char *)(dst + n) =
				*(unsigned char *)(src + n);
	}
	return (dst);
}
