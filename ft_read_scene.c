/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:52:51 by kmieshko          #+#    #+#             */
/*   Updated: 2018/07/25 16:52:52 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// t_mlx	*ft_create_mlx(void) //////////// delete
// {
// 	t_mlx *mlx;

// 	mlx = (t_mlx *)malloc(sizeof(t_mlx));
// 	mlx->mlx = NULL;
// 	mlx->win = NULL;
// 	mlx->img = NULL;
// 	mlx->size_line = 0;
// 	mlx->bpp = 0;
// 	mlx->endian = 0;
// 	mlx->addr = NULL;
// 	mlx->width = 600;
// 	mlx->height = 600;
// 	mlx->color = 0xffffff;
// 	return (mlx);
// }

int			ft_check_type(char *line)
{
	if (ft_strcmp(line, "sphere") != 0 &&
		ft_strcmp(line, "plane") != 0 &&
		ft_strcmp(line, "cylinder") != 0 &&
		ft_strcmp(line, "cone") != 0 &&
		ft_strcmp(line, "light") != 0 &&
		ft_strcmp(line, "camera") != 0)
		return (0);
	return (1);
}

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

void	ft_incorrect(char *type)
{
	ft_putstr("Error: Incorrect ");
	ft_putstr(type);
	ft_putstr(" parameters!\n");
	system("leaks -q a.out");
	exit(0);
}

void	ft_free(void **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void		ft_read_scene(char *str, t_closest *closest)
{
	int		fd;
	int		i;
	void	**res;
	char	*line;
	char	**type;
	
	i = 0;
	line = NULL;
	int	cam = 0;
	int	light = 0;
	fd = open(str, O_RDONLY);
	closest->light = (t_light **)malloc(sizeof(t_light *) * 12);
	int k = 0;
	while (k < 12)
	{
		closest->light[k] = NULL;
		k++;
	}
	int j = 0;
	while (get_next_line(fd, &(line)))
	{
		line = ft_tolowercase(line);
		if (ft_check_type(line) == 1)
		{
			if (ft_strcmp(line, "sphere") == 0)
			{
				closest->figure[i] = ft_create_sphere(fd, line);
				closest->type[i] = "sphere";
			}
			else if (ft_strcmp(line, "plane") == 0)
			{
				closest->figure[i] = ft_create_plane(fd, line);
				closest->type[i] = "plane";
			}
			else if (ft_strcmp(line, "cylinder") == 0)
			{
				closest->figure[i] = ft_create_cylinder(fd, line);
				closest->type[i] = "cylinder";	
			}
			else if (ft_strcmp(line, "cone") == 0)
			{
				closest->figure[i] = ft_create_cone(fd, line);
				closest->type[i] = "cone";	
			}
			else if (ft_strcmp(line, "light") == 0)
			{
				if (j <= 10)
				{
					closest->figure[i] = ft_create_light(fd, line);
					closest->light[j] = closest->figure[i];
					closest->type[i] = "light";
					light++;
					j++;
				}
				else
				{
					ft_putstr("Error: Wrong number of light!\n");
					system("leaks -q a.out");
					exit(0);
				}
			}
			else if (ft_strcmp(line, "camera") == 0)
			{
				closest->figure[i] = ft_create_camera(fd, line);
				closest->cam = closest->figure[i];
				closest->type[i] = "camera";
				cam++;
			}
			i++;
			closest->nb_fig++;
			free(line);
		}
		else
		{
			ft_putstr("Error: Wrong scene!\n");
			free(line);
			system("leaks -q a.out");
			exit(0);
		}
	}
	if (cam != 1)
	{
		ft_putstr("Error: Wrong number of camera!\n");
		system("leaks -q a.out");
		exit(0);
	}
	else if (!light)
	{
		ft_putstr("Error: Wrong number of light!\n");
		system("leaks -q a.out");
		exit(0);
	}
}
