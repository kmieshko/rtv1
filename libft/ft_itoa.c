/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 12:25:32 by kmieshko          #+#    #+#             */
/*   Updated: 2017/11/24 12:25:33 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(long int nb)
{
	size_t	count;

	count = 1;
	while (nb /= 10)
		count++;
	return (count);
}

char			*ft_itoa(int nbr)
{
	long int	n;
	size_t		count;
	char		*arr;

	n = (long int)nbr;
	count = ft_count(n);
	if (nbr < 0)
	{
		n = -n;
		count++;
	}
	if (!(arr = ft_strnew(count)))
		return (NULL);
	arr[--count] = n % 10 + 48;
	while (n /= 10)
		arr[--count] = n % 10 + 48;
	if (nbr < 0)
		arr[0] = '-';
	return (arr);
}
