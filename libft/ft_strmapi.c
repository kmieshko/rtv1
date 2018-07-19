/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 14:17:24 by kmieshko          #+#    #+#             */
/*   Updated: 2017/10/31 14:17:25 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	count;
	char			*arr;

	i = 0;
	count = 0;
	if (!s || !f)
		return (NULL);
	while (s[count] != '\0')
		count++;
	if (!(arr = (char *)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		arr[i] = f(i, s[i]);
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
