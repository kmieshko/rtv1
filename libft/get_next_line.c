/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:12:28 by kmieshko          #+#    #+#             */
/*   Updated: 2018/01/25 17:20:15 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gnl	*create_gnl(t_gnl **gnl, int fd, char *buf)
{
	t_gnl	*tmp;
	char	*arr;

	tmp = *gnl;
	while (tmp)
	{
		if (tmp->fd == fd)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		arr = tmp->content;
		if (!(tmp->content = join(arr, buf)))
			return (NULL);
		tmp->content_size = ft_strlen(tmp->content) + 1;
	}
	else
	{
		if (!(tmp = (t_gnl *)ft_lstnew(buf, (ft_strlen(buf) + 1))))
			return (NULL);
		tmp->fd = fd;
		ft_lstadd((t_list **)gnl, (t_list *)tmp);
	}
	return (tmp);
}

static t_gnl	*fill_gnl(int i, char *arr, t_gnl **gnl)
{
	t_gnl	*tmp;
	int		len;

	len = 0;
	tmp = *gnl;
	if ((ft_strchr(arr, '\n')) != NULL)
	{
		len = ft_strlen(ft_strchr(arr, '\n') + 1);
		if (len == 0)
		{
			tmp->content = NULL;
			tmp->content_size = 0;
		}
		else
		{
			tmp->content = ft_strsub(arr, i + 1, tmp->content_size);
			tmp->content_size = tmp->content_size - i - 1;
		}
	}
	else
	{
		tmp->content = NULL;
		tmp->content_size = 0;
	}
	return (tmp);
}

static char		*fill_line(t_gnl **gnl, int fd, char *buf)
{
	t_gnl	*tmp;
	char	*arr;
	char	*str;
	int		i;

	tmp = *gnl;
	i = 0;
	while (tmp)
	{
		if (tmp->fd == fd)
			break ;
		tmp = tmp->next;
	}
	arr = tmp->content;
	if (arr == NULL)
		return (NULL);
	while (arr[i] != '\n' && arr[i] != '\0')
		i++;
	if (!(str = ft_strsub(arr, 0, i)))
		return (NULL);
	tmp = fill_gnl(i, arr, &tmp);
	ft_strdel(&buf);
	ft_strdel(&arr);
	return (str);
}

static int		ft_main_condition(char *buf)
{
	if (buf != NULL)
		ft_strdel(&buf);
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	static t_gnl	*gnl;
	char			*buf;
	int				i;

	buf = NULL;
	if (fd < 0 || !line || BUFF_SIZE < 1 || !(buf = ft_strnew(BUFF_SIZE)) ||
		read(fd, buf, 0) < 0)
		return (ft_main_condition(buf));
	while ((i = read(fd, buf, BUFF_SIZE)) != 0)
	{
		buf[i] = '\0';
		if (!(gnl = create_gnl(&gnl, fd, buf)))
			return (-1);
		if (ft_strchr(gnl->content, '\n') != NULL)
			if ((*line = fill_line(&gnl, fd, buf)) != NULL)
				return (1);
	}
	if (!gnl)
		if (!(gnl = create_gnl(&gnl, fd, buf)))
			return (-1);
	if ((*line = fill_line(&gnl, fd, buf)) != NULL)
		return (1);
	ft_strdel(&buf);
	return (0);
}
