/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:36:52 by kmieshko          #+#    #+#             */
/*   Updated: 2017/10/31 16:36:53 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*arr;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(arr = (char *)malloc(sizeof(char) * ((int)ft_strlen(s1)
		+ (int)ft_strlen(s2) + 1))))
		return (NULL);
	while (i < (int)ft_strlen(s1))
	{
		arr[i] = s1[i];
		i++;
	}
	while (i < (int)ft_strlen(s1) + (int)ft_strlen(s2))
	{
		arr[i] = s2[j];
		i++;
		j++;
	}
	arr[i] = '\0';
	return (arr);
}
