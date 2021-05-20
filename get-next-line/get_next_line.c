/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:30:06 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/20 23:39:54 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	int					result;
	static t_buffchunk	bc = {NULL, 0, 0, -1, {0}};

	*line = NULL;
	if (fd < 0 || line == NULL)
		;
	else
	{
		if (bc.num_line > 0)
		{
			*line = gnl_buffsplit(&bc);
			bc.num_line--;
		}
		else
		{
			make_bc(fd, &bc);
			*line = gnl_buffsplit(&bc);
			bc.num_line--;
		}
	}
	if (bc.status != 1 && bc.num_line == 0)
		result = bc.status;
	else
		result = 1;
	return (result);
}
