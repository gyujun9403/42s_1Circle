/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygj <ygj@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:07:21 by ygj               #+#    #+#             */
/*   Updated: 2021/05/29 01:45:43 by ygj              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_bufflst	*find_lastlst(t_bufflst *lst)
{
	t_bufflst	*last;

	last = lst;
	if (lst != NULL)
	{
		while (last->next != NULL)
			last = last->next;
	}
	return (last);
}

t_bufflst	*malloc_lastlst(t_bufflst **lst)
{
	t_bufflst	*last;

	if (*lst == NULL)
	{
		*lst = (t_bufflst *)malloc(sizeof(t_bufflst));
		if (*lst == NULL)
			free_lst(lst, FREE_ALL);
		last = *lst;
	}
	else
	{
		last = find_lastlst(*lst);
		last->next = (t_bufflst *)malloc(sizeof(t_bufflst));
		if (last == NULL)
			free_lst(lst, FREE_ALL);
		else
			last = last->next;
	}
	return (last);
}

t_bufflst	*add_lastlst(t_bufflst **lst)
{
	t_bufflst	*last;

	last = malloc_lastlst(lst);
	if (last != NULL)
	{
		last->is_eof = 0;
		last->num_nl = 0;
		last->next = NULL;
		last->buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (last->buff == NULL)
		{
			free_lst(lst, FREE_ALL);
			last = NULL;
		}
		else
		{
			last->state = 0;
			last->st_buff = last->buff;
		}
	}
	return (last);
}

t_bufflst	*free_lst(t_bufflst **lst, short flg)
{
	t_bufflst	*temp;

	temp = NULL;
	if (flg == FREE_ONE)
	{
		temp = (*lst)->next;
		free((*lst)->buff);
		free(*lst);
		*lst = temp;
	}
	else
	{
		while (*lst != NULL)
		{
			temp = (*lst)->next;
			free((*lst)->buff);
			(*lst)->buff = NULL;
			free(*lst);
			*lst = NULL;
			*lst = temp;
		}
	}
	return (temp);
}

size_t		gnl_strchr(const char *s, int c)
{
	size_t	i;
	char	*answer;

	i = 0;
	answer = NULL;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == (unsigned char)c)
		{
			answer = (char *)s + i;
			break ;
		}
		i++;
	}
	if (*(s + i) == '\0' && (unsigned char)c == '\0')
		answer = (char *)s + i;
	return (i);
}
