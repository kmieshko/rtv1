/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:23:18 by kmieshko          #+#    #+#             */
/*   Updated: 2017/11/01 11:23:19 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*arr;
	size_t	i;

	i = 0;
	if (!(arr = (char *)malloc(sizeof(char) * (int)size)))
		return (NULL);
	while (i < size)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}
