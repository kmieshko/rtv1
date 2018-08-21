/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addit_for_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 11:21:03 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/15 11:21:04 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	*ft_tolowercase(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int		ft_count_coord(char *str)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}

void	ft_free(void **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

int		ft_check_type(char *line)
{
	if (ft_strcmp(line, "sphere") != 0 &&
		ft_strcmp(line, "plane") != 0 &&
		ft_strcmp(line, "cylinder") != 0 &&
		ft_strcmp(line, "cone") != 0 &&
		ft_strcmp(line, "light") != 0 &&
		ft_strcmp(line, "camera") != 0 &&
		ft_strcmp(line, "rotation") != 0)
		return (0);
	return (1);
}
