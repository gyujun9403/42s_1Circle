/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:02:38 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/14 22:57:47 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*pt;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	pt = malloc(sizeof(char) * len + 1);
	if (pt != NULL)
		while (i <= len)
		{
			*(pt + i) = *(s1 + i);
			i++;
		}
	return (pt);
}
