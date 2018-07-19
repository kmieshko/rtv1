/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:55:51 by kmieshko          #+#    #+#             */
/*   Updated: 2017/10/27 15:55:52 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (dstsize != 0)
	{
		while (dst[count] != '\0' && count < dstsize)
			count++;
		i = count;
		while (i < dstsize - 1 && src[i - count] != '\0')
		{
			dst[i] = src[i - count];
			i++;
		}
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (count + ft_strlen(src));
}
