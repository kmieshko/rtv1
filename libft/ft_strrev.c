/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:38:07 by kmieshko          #+#    #+#             */
/*   Updated: 2017/11/10 12:38:08 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		max;
	int		min;
	char	temp;

	if (!str)
		return (NULL);
	max = 0;
	min = 0;
	while (str[max] != '\0')
		max++;
	max = max - 1;
	while (max >= 0)
	{
		temp = str[min];
		str[min] = str[max];
		str[max] = temp;
		max--;
		min++;
	}
	return (str);
}
