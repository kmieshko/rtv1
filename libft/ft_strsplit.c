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

static void		*ft_ret_null(char **arr, int j)
{
	while (j > 0)
	{
		free(arr[j]);
		j--;
	}
	free(arr);
	return (NULL);
}

static int		ft_count_word(const char *str, char c)
{
	int		count;
	int		flag;
	int		i;

	flag = 0;
	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (flag == 1 && str[i] == c)
			flag = 0;
		if (flag == 0 && str[i] != c)
		{
			flag = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int		ft_word_length(const char *str, char c)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		nb_word;
	int		i;

	i = 0;
	nb_word = ft_count_word(s, c);
	if (!s || !(arr = (char **)malloc(sizeof(char *) *
		ft_count_word(s, c) + 1)))
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		arr[i] = ft_strsub(s, 0, ft_word_length(s, c));
		if (arr[i] == NULL)
			return (ft_ret_null(arr, i));
		s = s + ft_word_length(s, c);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
