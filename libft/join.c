/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 14:34:43 by kmieshko          #+#    #+#             */
/*   Updated: 2018/05/31 14:34:45 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*join(char *s1, char *s2)
{
	char	*arr;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = s1 == NULL ? 0 : ft_strlen(s1);
	len2 = s2 == NULL ? 0 : ft_strlen(s2);
	if (!(arr = ft_strnew(len1 + len2 + 1)))
		return (NULL);
	if (len1 > 0)
		arr = ft_strcpy(arr, s1);
	arr = ft_strcat(arr, s2);
	ft_strdel(&s1);
	return (arr);
}
