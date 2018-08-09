/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:22:57 by kmieshko          #+#    #+#             */
/*   Updated: 2017/10/30 17:23:00 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		count;
	char	*arr;

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
		arr[i] = f(s[i]);
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
