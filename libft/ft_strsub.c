/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:14:51 by kmieshko          #+#    #+#             */
/*   Updated: 2017/10/31 16:14:53 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*arr;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(arr = (char *)malloc(sizeof(char) * ((int)len + 1))))
		return (NULL);
	while ((int)len > 0)
	{
		arr[i] = s[start];
		i++;
		start++;
		len--;
	}
	arr[i] = '\0';
	return (arr);
}
