/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:52:24 by kmieshko          #+#    #+#             */
/*   Updated: 2017/11/17 10:52:25 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_lstclear(t_list *list)
{
	t_list	*temp;

	temp = NULL;
	while (list)
	{
		if (list->next)
			temp = list->next;
		else
			temp = NULL;
		free(list);
		list = temp;
	}
	list = NULL;
	return (NULL);
}
