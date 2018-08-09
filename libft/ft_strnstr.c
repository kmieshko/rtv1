/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 13:43:02 by kmieshko          #+#    #+#             */
/*   Updated: 2017/10/27 13:43:04 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = ft_strlen(needle);
	if (count == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0' && count + i <= len)
	{
		j = 0;
		while (haystack[j + i] == needle[j])
		{
			if (j == count - 1)
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
