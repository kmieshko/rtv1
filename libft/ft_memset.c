/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:06:11 by kmieshko          #+#    #+#             */
/*   Updated: 2017/10/26 10:06:13 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memptr, int val, size_t num)
{
	size_t	i;
	char	*arr;

	i = 0;
	arr = (char *)memptr;
	while (i < num)
	{
		arr[i] = val;
		i++;
	}
	return (memptr);
}
