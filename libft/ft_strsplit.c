/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:06:43 by kmieshko          #+#    #+#             */
/*   Updated: 2017/11/01 14:06:44 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_letter(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static void	*ft_ret_null(char **arr, int j)
{
	while (j > 0)
	{
		free(arr[j]);
		j--;
	}
	free(arr);
	return (NULL);
}

char		**ft_strsplit(char const *s, char c)
{
	t_iterators	iter;
	char		**arr;

	iter.i = 0;
	iter.j = 0;
	if (!s || !(arr = (char **)malloc(sizeof(char *) * ft_word(s, c) + 1)))
		return (NULL);
	while (s[iter.i] != '\0')
	{
		iter.k = 0;
		while (s[iter.i] == c && s[iter.i] != '\0')
			iter.i++;
		if (s[iter.i] != '\0')
		{
			if (!(arr[iter.j] =
				(char *)malloc(sizeof(char) * ft_letter(s, c) + 1)))
				return (ft_ret_null(arr, iter.j));
			while (s[iter.i] != '\0' && s[iter.i] != c)
				arr[iter.j][iter.k++] = s[iter.i++];
			arr[iter.j++][iter.k] = '\0';
		}
	}
	arr[iter.j] = NULL;
	return (arr);
}
