/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:40:52 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/14 16:40:53 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	if_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int	if_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int			clamp(int color)
{
	int res;

	res = if_min(255, if_max(0, color));
	return (res);
}
