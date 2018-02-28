/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:30:51 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:45:12 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_line(char *buffer)
{
	int		count;
	char	*tmp;

	count = 0;
	if (buffer)
	{
		while (buffer[count] != '\0')
		{
			if (buffer[count] == '\n')
				break ;
			count++;
		}
		tmp = ft_strsub(buffer, 0, count);
		return (tmp);
	}
	return (NULL);
}

static int	ft_get_save(char **line, char **save)
{
	(*line) = ft_get_line(*save);
	(*save) = ft_strfsub(*save, ft_strnlen(*save, '\n') + 1, ft_strlen(*save));
	return (1);
}

static int	ft_check_return(char **save, char **line, int ret)
{
	int		count;

	ft_memdel((void**)line);
	if (ret < 0)
	{
		ft_memdel((void**)save);
		ft_memdel((void**)line);
		return (-1);
	}
	count = ft_strlen(*save);
	if (count == 0)
	{
		ft_memdel((void**)save);
		return (0);
	}
	(*line) = ft_strdup(*save);
	ft_memdel((void**)save);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*save = NULL;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (ft_strchr(save, '\n'))
		return (ft_get_save(line, &save));
	if (save == NULL)
		save = ft_strnew(0);
	if (!((*line) = (char*)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	while (!(ft_strchr(save, '\n')))
	{
		if ((ret = read(fd, (*line), BUFF_SIZE)) < 1)
			return (ft_check_return(&save, line, ret));
		(*line)[ret] = '\0';
		save = ft_strjoin_fl(save, *line);
	}
	*line != NULL ? ft_strdel(line) : NULL;
	(*line) = ft_get_line(save);
	if ((ft_strchr(save, '\n')) != 0)
		save = ft_strfsub(save, ft_strnlen(save, '\n') + 1, ft_strlen(save));
	return ((ret > 1) ? (1) : ret);
}
