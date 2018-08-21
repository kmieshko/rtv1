/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:50:02 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/13 17:50:03 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		dot_product(double *a, double *b)
{
	double	sum;
	size_t	i;

	i = 0;
	sum = 0;
	while (i < 3)
	{
		sum += a[i] * b[i];
		i++;
	}
	return (sum);
}

double		length(double *vector)
{
	double	length;

	length = sqrt(dot_product(vector, vector));
	return (length);
}
