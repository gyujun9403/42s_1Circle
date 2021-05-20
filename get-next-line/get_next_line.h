/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:29:39 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/20 23:48:16 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>

typedef	struct	s_buffchunk
{
	char	*buff_chunk;
	size_t	leng_bc;
	size_t	num_line;
	short	status;
	char	buff[BUFFER_SIZE];
}				t_buffchunk;

int				get_next_line(int fd, char **line);
void			make_bc(int fd, t_buffchunk *bc);
void			gnl_buffcat(size_t len, t_buffchunk *bc);
size_t			gnl_buffcpy(char *s1, char *s2, size_t until);
char			*gnl_buffsplit(t_buffchunk *bc);

#endif
