/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 14:09:44 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/06 14:09:45 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

double		ft_atod(char *str)
{
	double	n;
	int		flag;
	char	**arr;

	flag = 1;
	if (!(ft_strchr(str, '.')))
		return (ft_atoi(str));
	else
	{
		arr = ft_strsplit(str, '.');
		n = ft_atoi(arr[0]);
		if (n < 0)
		{
			flag = -1;
			n = -n;
		}
		if (!(arr[1][0] >= '0' && arr[1][0] <= '9'))
			return (0);
		n += (double)ft_atoi(arr[1]) / ft_recursive_power(10, ft_strlen(arr[1]));
		ft_free(arr);
	}
	return (n * flag);
}