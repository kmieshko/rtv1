/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 13:41:40 by kmieshko          #+#    #+#             */
/*   Updated: 2017/11/01 13:41:41 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *str)
{
	int		count;

	count = 0;
	if (!str || str[count] == '\0')
		return (count);
	while (str[count] != '\0')
		count++;
	count = count - 1;
	return (count);
}

static int	ft_start(char const *str)
{
	int	start;

	start = 0;
	while ((str[start] == ' ' || str[start] == '\n' || str[start] == '\t')
		&& str[start] != '\0')
		start++;
	return (start);
}

static int	ft_end(char const *str)
{
	int	count;
	int end;
	int	start;

	end = 0;
	start = ft_start(str);
	count = ft_count(str);
	if (ft_strlen(str) - start > 0)
	{
		while ((str[count] == ' ' || str[count] == '\n' || str[count] == '\t'))
		{
			end++;
			count--;
		}
	}
	return (end);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		start;
	int		end;
	int		count;
	char	*arr;

	if (!s)
		return (0);
	i = 0;
	count = ft_count(s);
	end = ft_end(s);
	start = ft_start(s);
	if (!(arr = (char *)malloc(sizeof(char) *
		(ft_strlen(s) - end - start + 1))))
		return (NULL);
	while (i + start <= count - end)
	{
		arr[i] = s[i + start];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
