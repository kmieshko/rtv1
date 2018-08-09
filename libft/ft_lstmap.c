/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:43:31 by kmieshko          #+#    #+#             */
/*   Updated: 2017/11/10 10:43:32 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlist;
	t_list	*tail;

	newlist = NULL;
	tail = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		if (newlist == NULL)
		{
			if (!(newlist = ft_lstnew(f(lst)->content, f(lst)->content_size)))
				return (NULL);
			tail = newlist;
		}
		else
		{
			if (!(tail->next =
				ft_lstnew(f(lst)->content, f(lst)->content_size)))
				return (ft_lstclear(newlist));
			tail = tail->next;
		}
		lst = lst->next;
	}
	return (newlist);
}
