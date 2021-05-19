/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:29:39 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/19 16:40:42 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>

struct	s_buffchunk
{
	char	*buff_chunk;
	size_t	leng_bc;
	size_t	num_line;
}typedef	t_buffchunk;

//int		get_buff(int fd, char *buff);
//size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
int		get_next_line(int fd, char **line);
int	make_bc(int fd, char *buff, t_buffchunk *bc);
void	GNL_buffcat(char *buff, size_t len, t_buffchunk *bc);

# endif
