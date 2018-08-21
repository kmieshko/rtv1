/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 11:44:33 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/06 11:44:34 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_center(t_light *light, char *tmp)
{
	char **del;

	if (ft_count_coord(tmp) == 0)
		ft_incorrect("light");
	del = ft_strsplit(tmp, ',');
	light->xyz[0] = ft_atod(del[0]);
	light->xyz[1] = ft_atod(del[1]);
	light->xyz[2] = ft_atod(del[2]);
	ft_free((void **)del);
}

static void	ft_type(t_light *light, char *tmp)
{
	if (light->type)
		ft_incorrect("light");
	else
		light->type = ft_strtrim(tmp);
	if (ft_strcmp(light->type, "ambient") != 0 &&
		ft_strcmp(light->type, "point") != 0)
		ft_incorrect("light");
}

static int	ft_main_condition(t_light *light, char **tmp, char *arr, int k)
{
	arr = ft_strtrim(tmp[0]);
	if (tmp[1])
	{
		if (ft_strcmp(arr, "center") == 0)
			ft_center(light, tmp[1]);
		else if (ft_strcmp(arr, "type") == 0)
			ft_type(light, tmp[1]);
		else if (ft_strcmp(arr, "intensity") == 0)
		{
			light->intensity = ft_atod(tmp[1]);
			if (light->intensity < 0)
				light->intensity = 0;
		}
		else
			ft_incorrect("light");
		if (arr)
			free(arr);
	}
	else
		ft_incorrect("light");
	ft_free((void **)tmp);
	return (k + 1);
}

t_light		*ft_create_light(int fd, char *line, int iter, t_closest *closest)
{
	t_light	*light;
	char	**tmp;

	closest->type[iter] = "light";
	light = (t_light *)malloc(sizeof(t_light));
	light->type = NULL;
	iter = 0;
	while (iter < 3)
	{
		if (get_next_line(fd, &(line)))
		{
			line = ft_tolowercase(line);
			tmp = ft_strsplit(line, ':');
			free(line);
			if (tmp[0])
				iter = ft_main_condition(light, tmp, NULL, iter);
			else
				ft_wrong("light");
		}
		else
			ft_wrong("light");
	}
	return (light);
}
