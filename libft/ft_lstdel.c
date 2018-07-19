/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:24:01 by kmieshko          #+#    #+#             */
/*   Updated: 2017/11/02 17:24:02 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*nextlist;

	if (!alst || !*alst || !del)
		return ;
	list = *alst;
	while (list)
	{
		nextlist = list;
		del(list->content, list->content_size);
		free(list);
		list = nextlist->next;
	}
	*alst = NULL;
}
