/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 11:17:28 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/15 11:17:29 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_incorrect(char *type)
{
	ft_putstr("Error: Incorrect ");
	ft_putstr(type);
	ft_putstr(" parameters!\n");
	exit(0);
}

void	ft_wrong(char *type)
{
	ft_putstr("Error: Wrong ");
	ft_putstr(type);
	ft_putstr("!\n");
	exit(0);
}

void	ft_null_line(char *line)
{
	if (line == NULL)
	{
		ft_putstr("Error: invalid argument!\n");
		exit(0);
	}
}

int		ft_manage(int key)
{
	if (key == 53)
		exit(0);
	return (0);
}

int		ft_exit_mouse(void)
{
	exit(0);
}
