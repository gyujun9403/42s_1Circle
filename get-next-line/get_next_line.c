/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:41:10 by ygj               #+#    #+#             */
/*   Updated: 2021/06/03 12:46:31 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			get_next_line(int fd, char **line)
{
	short				value_return;
	static	t_bufflst	*arr[OPEN_MAX] = {NULL};

	value_return = -1;
	if (fd >= 0 && fd < OPEN_MAX && BUFFER_SIZE > 0 && line)
	{
		if (arr[fd] == NULL || (arr[fd] != NULL && arr[fd]->num_nl == 0))
			while (rnadd_lst(fd, &arr[fd]) && !find_lastlst(arr[fd])->num_nl)
				;
		if (arr[fd] != NULL)
		{
			*line = get_line(&arr[fd]);
			if (*line != NULL)
			{
				if (arr[fd]->is_eof == 1 && arr[fd]->num_nl == 0)
				{
					free_lst(&arr[fd], FREE_ALL);
					value_return = 0;
				}
				else
					value_return = 1;
			}
		}
	}
	return (value_return);
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
	if (lst->leng != BUFFER_SIZE)
		lst->num_nl++;
}

t_bufflst	*rnadd_lst(int fd, t_bufflst **lst)
{
	t_bufflst	*last_lst;

	last_lst = add_lastlst(lst);
	if (last_lst != NULL)
	{
		last_lst->leng = read(fd, last_lst->buff, BUFFER_SIZE);
		if (last_lst->leng != ERR)
		{
			*(last_lst->buff + last_lst->leng) = '\0';
			cnt_nl(last_lst);
			if (last_lst->leng != BUFFER_SIZE)
				last_lst->is_eof = 1;
			return (*lst);
		}
		else
			free_lst(lst, FREE_ALL);
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
		len_line += temp->leng;
		temp = temp->next;
	}
	while (*(temp->st_buff + idx) != '\n' && *(temp->st_buff + idx))
		idx++;
	len_line += idx;
	if (temp->leng > 0)
		temp->leng -= ++idx;
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
		free_lst(lst, FREE_ALL);
		return (line);
	}
	while ((*lst)->num_nl == 0)
	{
		while (*((*lst)->st_buff) != '\0')
			*(line + idx++) = *((*lst)->st_buff++);
		free_lst(lst, FREE_ONE);
	}
	while (*((*lst)->st_buff) != '\n' && *((*lst)->st_buff))
		*(line + idx++) = *((*lst)->st_buff++);
	*(line + idx++) = '\0';
	if (*((*lst)->st_buff) == '\n')
		(*lst)->st_buff++;
	(*lst)->num_nl--;
	return (line);
}
