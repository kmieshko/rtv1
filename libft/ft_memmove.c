/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:39:13 by kmieshko          #+#    #+#             */
/*   Updated: 2017/10/26 13:39:14 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, const void *s, size_t len)
{
	const char	*src;
	char		*dst;
	size_t		i;

	i = 0;
	src = (const char *)s;
	dst = (char *)d;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (src < dst)
	{
		while (len--)
			dst[len] = src[len];
	}
	else
		while (len--)
		{
			dst[i] = src[i];
			i++;
		}
	return (dst);
}
