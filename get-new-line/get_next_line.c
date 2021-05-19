/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:30:06 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/19 17:14:50 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	int result;
	char buff[BUFFER_SIZE];
	static t_buffchunk bc = {NULL, 0, 0};

	result = -1;
	*line = NULL;
	if (fd < 0 || line == NULL)
		;
	else
	{
		result = make_bc(fd, buff, &bc);
	}
	return (result);
}
