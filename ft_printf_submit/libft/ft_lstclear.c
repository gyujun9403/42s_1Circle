/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygj <ygj@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:37:50 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/02 13:32:50 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *temp;

	if (del != NULL)
	{
		while (*lst != NULL)
		{
			del((*lst)->content);
			temp = *lst;
			*lst = (*lst)->next;
			free(temp);
		}
	}
}
