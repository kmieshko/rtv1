/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 11:29:38 by kmieshko          #+#    #+#             */
/*   Updated: 2017/10/26 11:29:42 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *str1;
	unsigned char *str2;

	if (dst == NULL && src == NULL)
		return (NULL);
	str1 = (unsigned char *)src;
	str2 = (unsigned char *)dst;
	while (n > 0)
	{
		*str2++ = *str1++;
		n--;
	}
	return (dst);
}
