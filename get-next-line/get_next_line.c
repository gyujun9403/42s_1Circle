/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygj <ygj@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:41:10 by ygj               #+#    #+#             */
/*   Updated: 2021/05/27 13:33:28 by ygj              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	short				not_first;
	static	t_bufflst	*arr[OPEN_MAX] = {NULL};

	not_first = 1;
	if (fd >= 0 || fd <= OPEN_MAX || BUFFER_SIZE > 0 || line)
	{
		if (arr[fd] == NULL)
			not_first = 0;
		if (arr[fd] == NULL || (arr[fd] != NULL && arr[fd]->num_nl == 0))
		{
			read_n_addlist(fd, &arr[fd]);
			while (arr[fd] != NULL && find_lastlst(arr[fd])->num_nl == 0)
				read_n_addlist(fd, &arr[fd]);
		}
		if (arr[fd] != NULL)
		{
			*line = get_line(&arr[fd]);
			if (*line != NULL)
				if (arr[fd]->is_eof == 1 && arr[fd]->num_nl == 0 && not_first)
					return (0);
				else
					return (1);
		}
	}
	return (-1);
}

void	cnt_nl(t_bufflst *lst)
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

void	read_n_addlist(int fd, t_bufflst **lst)
{
	t_bufflst	*last_lst;

	last_lst = add_lastlst(lst);
	if (last_lst->state != ERR)
	{
		last_lst->state = read(fd, last_lst->buff, BUFFER_SIZE);
		if (last_lst->state != ERR)
		{
			*(last_lst->buff + last_lst->state) = '\0';
			cnt_nl(last_lst);
			if (last_lst->state != BUFFER_SIZE)
				last_lst->is_eof = 1;
		}
	}
	if (last_lst->state == ERR)
		free_lst(lst, 1);
}

char	*get_line(t_bufflst **lst)
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

char	*buffcat(t_bufflst **lst, size_t len_line)
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
