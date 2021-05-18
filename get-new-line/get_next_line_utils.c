/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:30:27 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/18 16:01:45 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_buff_n_status(int fd, char *buff, size_t *len)
{
	char	c;
	size_t	byte;
	size_t	len;
	
	len = 0;
	byte = read(fd, &c, sizeof(char));
	while (c != '\n' && byte == 1)
	{
		*(buff + len++) = c;
		byte = read(fd, &c, sizeof(char));
	}
	return (byte);
}
