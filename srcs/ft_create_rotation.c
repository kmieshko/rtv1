/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 12:39:26 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/10 12:39:27 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_angle(t_rotation *rot, char *tmp)
{
	char	**del;
	int		i;

	i = 0;
	if (ft_count_coord(tmp) == 0)
		ft_incorrect("rotation");
	del = ft_strsplit(tmp, ',');
	rot->angle[0] = ft_atoi(del[0]);
	rot->angle[1] = ft_atoi(del[1]);
	rot->angle[2] = ft_atoi(del[2]);
	ft_free((void **)del);
}

static void	ft_main_condition(t_rotation *rot, char **tmp, char *arr)
{
	arr = ft_strtrim(tmp[0]);
	if (tmp[1])
	{
		if (ft_strcmp(arr, "angle") == 0)
			ft_angle(rot, tmp[1]);
		else
			ft_incorrect("rotation");
		if (arr)
			free(arr);
	}
	else
		ft_incorrect("rotation");
}

t_rotation	*ft_create_rotation(int fd, char *line, int iter,
	t_closest *closest)
{
	char		**tmp;
	t_rotation	*rot;

	rot = (t_rotation *)malloc(sizeof(t_rotation));
	if (get_next_line(fd, &(line)))
	{
		line = ft_tolowercase(line);
		tmp = ft_strsplit(line, ':');
		free(line);
		if (tmp[0])
		{
			ft_main_condition(rot, tmp, NULL);
			ft_free((void **)tmp);
		}
		else
			ft_wrong("rotation");
	}
	else
		ft_wrong("rotation");
	closest->type[iter] = "rotation";
	return (rot);
}
