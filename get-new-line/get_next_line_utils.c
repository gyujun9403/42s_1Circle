/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:30:27 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/19 18:36:48 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	GNL_buffcat(char *buff, size_t len, t_buffchunk *bc)
{
	char *temp;
	size_t	index;
	size_t	index_buff;

	index = 0;
	index_buff = 0;
	if (buff == NULL)
	{}
	else if (bc->buff_chunk == NULL)
	{
		bc->buff_chunk = (char *)malloc(sizeof(char) * (len + 1));
		bc->leng_bc = len;
		while (index < len)
		{
			*(bc->buff_chunk + index) = *(buff + index);
			index++;
		}
	}
	else
	{
		temp = bc->buff_chunk;
		bc->buff_chunk = (char *)malloc(sizeof(char) * (bc->leng_bc + 1));
		while (index < bc->leng_bc)
		{
			*(bc->buff_chunk + index) = *(temp + index);
			index++;
		}
		bc->leng_bc += len;
		while (index_buff < len)
		{
			*(bc->buff_chunk + index) = *(buff + index_buff);
			index++;
			index_buff++;
		}
		free(temp);
	}
}

int	make_bc (int fd, char *buff, t_buffchunk *bc)
{

	int		byte;
	char	c;
	size_t	index;

	byte = 1;
	index = 0;
	while (byte == 1)//&& bc->num_line == 0)
	{
		index = 0;
		byte = read(fd, &c, sizeof(char));
		while (byte == 1 && index < BUFFER_SIZE)
		{
			if (c == '\n')
				bc->num_line++;
			*(buff + index++) = c;
			byte = read(fd, &c, sizeof(char));
		}
		if (c != '\n' && byte == 0)
			bc->num_line++;
		GNL_buffcat(buff, index, bc);
	}
	return (byte);
}
