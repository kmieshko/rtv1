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

t_light	*ft_create_light(int fd, char *line)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	int		k;

	k = 0;
	while (k < 3)
	{
		if (get_next_line(fd, &(line)))
		{
			ft_tolowercase(line);
			char	**tmp;
			char	*arr;
			tmp = ft_strsplit(line, ':');
			if (tmp[0])
				arr = ft_strtrim(tmp[0]);
			if (ft_strcmp(arr, "center") == 0)
			{
				if (ft_count_coord(tmp[1]) == 0)
					ft_incorrect("light");
				char **del;
				del = ft_strsplit(tmp[1], ',');
				light->xyz[0] = ft_atoi(del[0]);
				light->xyz[1] = ft_atoi(del[1]);
				light->xyz[2] = ft_atoi(del[2]);
				ft_free((void **)del);
			}
			else if (ft_strcmp(arr, "type") == 0)
			{
				light->type = ft_strtrim(tmp[1]);
				if (ft_strcmp(light->type, "ambient") != 0 &&
					ft_strcmp(light->type, "point") != 0)
					ft_incorrect("light");
			}
			else if (ft_strcmp(arr, "intensity") == 0)
			{
				light->intensity = ft_atod(tmp[1]);
				if (light->intensity < 0)
					light->intensity = 0;
			}
			else
				ft_incorrect("light");
			free(line);
			ft_free((void **)tmp);
			free(arr);
			k++;
		}
		else
		{
			ft_putstr("Error: Wrong light!");
			exit(0);
		}
	}
	return (light);
}
