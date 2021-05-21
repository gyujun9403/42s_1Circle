/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:30:27 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/21 00:55:25 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_buffcpy(char *dst, char *src, size_t until)
{
	size_t index;

	index = 0;
	while (index < until)
	{
		*(dst++) = *(src++);
		index++;
	}
	return (index);
}

char	*gnl_buffsplit(t_buffchunk *bc)
{
	char	*line;
	char	*temp;
	size_t	index;

	index = 0;
	while (*(bc->buff_chunk + index) != '\n'
			&& index < bc->leng_bc)
		index++;
	temp = bc->buff_chunk;
	if (bc->leng_bc > index + 1)
		bc->leng_bc -= (index + 1);
	else
		bc->leng_bc = 0;
	line = (char *)malloc(sizeof(char) * (index + 1));
	bc->buff_chunk = (char *)malloc(sizeof(char) * (bc->leng_bc));
	gnl_buffcpy(line, temp, index);
	*(line + index) = '\0';
	gnl_buffcpy(bc->buff_chunk, temp + index + 1, bc->leng_bc);
	free(temp);
	return (line);
}

void	gnl_buffcat(size_t len, t_buffchunk *bc)
{
	char	*temp;
	size_t	index;

	index = 0;
	if (bc->buff_chunk == NULL)
	{
		bc->buff_chunk = (char *)malloc(sizeof(char) * (len + 1));
		bc->leng_bc = len;
		gnl_buffcpy(bc->buff_chunk, bc->buff, len);
	}
	else
	{
		temp = bc->buff_chunk;
		bc->buff_chunk = (char *)malloc(sizeof(char) * (bc->leng_bc));
		index = gnl_buffcpy(bc->buff_chunk, temp, bc->leng_bc);
		bc->leng_bc += len;
		gnl_buffcpy(bc->buff_chunk + index, bc->buff, len);
		free(temp);
	}
}

void	make_bc(int fd, t_buffchunk *bc)
{
	int		byte;
	char	c;
	size_t	index;

	byte = 1;
	index = 0;
	while (byte == 1 && bc->num_line == 0)
	{
		index = 0;
		while (byte == 1 && index < BUFFER_SIZE)
		{
			byte = read(fd, &c, sizeof(char));
			if (c == '\n')
				bc->num_line++;
			*(bc->buff + index++) = c;
		}
		if (c != '\n' && byte == 0)
			bc->num_line++;
		bc->status = byte;
		gnl_buffcat(index, bc);
	}
}
