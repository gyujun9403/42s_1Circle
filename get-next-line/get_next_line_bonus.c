/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygj <ygj@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:41:10 by ygj               #+#    #+#             */
/*   Updated: 2021/05/27 21:19:55 by ygj              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int			get_next_line(int fd, char **line)
{
	static	t_bufflst	*arr[OPEN_MAX] = {NULL};

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (arr[fd] == NULL || (arr[fd] != NULL && arr[fd]->num_nl == 0))
		while (read_n_addlist(fd, &arr[fd])
		&& find_lastlst(arr[fd])->num_nl == 0)
			;
	if (arr[fd] == NULL)
		return (-1);
	*line = get_line(&arr[fd]);
	if (*line == NULL)
	{
		free_lst(&arr[fd], 1);
		return (-1);
	}
	if (arr[fd]->is_eof == 0 || arr[fd]->num_nl != 0)
		return (1);
	free_lst(&arr[fd], 1);
	return (0);
}

void		cnt_nl(t_bufflst *lst)
{
	short	flg;
	size_t	index;

	flg = 0;
	index = 0;
	while (*(lst->buff + index) != '\0')
	{
		if (*(lst->buff + index++) == '\n')
			lst->num_nl++;
	}
	if (lst->state != BUFFER_SIZE)
		lst->num_nl++;
}

t_bufflst	*read_n_addlist(int fd, t_bufflst **lst)
{
	t_bufflst	*last_lst;

	last_lst = add_lastlst(lst);
	if (last_lst != NULL)
	{
		last_lst->state = read(fd, last_lst->buff, BUFFER_SIZE);
		if (last_lst->state != ERR)
		{
			*(last_lst->buff + last_lst->state) = '\0';
			cnt_nl(last_lst);
			if (last_lst->state != BUFFER_SIZE)
				last_lst->is_eof = 1;
			return (*lst);
		}
		else
			free_lst(lst, 1);
	}
	return (NULL);
}

char		*get_line(t_bufflst **lst)
{
	size_t		len_line;
	size_t		idx;
	t_bufflst	*temp;

	len_line = 0;
	idx = 0;
	temp = *lst;
	while (temp->num_nl == 0)
	{
		len_line += temp->state;
		temp = temp->next;
	}
	while (*(temp->st_buff + idx) != '\n' && *(temp->st_buff + idx))
		idx++;
	len_line += idx;
	if (temp->state > 0)
		temp->state -= ++idx;
	return (buffcat(lst, len_line));
}

char		*buffcat(t_bufflst **lst, size_t len_line)
{
	size_t		idx;
	char		*line;

	idx = 0;
	line = (char *)malloc((len_line + 1) * sizeof(char));
	if (line == NULL)
	{
		free_lst(lst, 1);
		return (line);
	}
	while ((*lst)->num_nl == 0)
	{
		while (*((*lst)->st_buff) != '\0')
			*(line + idx++) = *((*lst)->st_buff++);
		free_lst(lst, 0);
	}
	while (*((*lst)->st_buff) != '\n' && *((*lst)->st_buff))
		*(line + idx++) = *((*lst)->st_buff++);
	*(line + idx++) = '\0';
	if (*((*lst)->st_buff) == '\n')
		(*lst)->st_buff++;
	(*lst)->num_nl--;
	return (line);
}
