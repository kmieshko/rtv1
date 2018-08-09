/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 10:42:16 by kmieshko          #+#    #+#             */
/*   Updated: 2018/08/06 10:42:17 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		ft_inbase(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + base - 10)) ||
		(c >= 'a' && c <= ('a' + base - 10)));
}

long long int	ft_atoi_base(char *str, int base)
{
	long long int	nb;
	int				flag;
	int				i;

	i = 0;
	nb = 0;
	if (base < 2 || base > 36)
		return (0);
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\f' || str[i] == ' '
		|| str[i] == '\n' || str[i] == '\0')
		i++;
	flag = (str[i] == '-' && base == 10) ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_inbase(str[i], base))
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * base + (str[i] - 48);
		else if (str[i] >= 'A' && str[i] <= 'F')
			nb = nb * base + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && str[i] <= 'f')
			nb = nb * base + (str[i] - 'a' + 10);
		i++;
	}
	return (nb * flag);
}
