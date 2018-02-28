/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 18:11:33 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/20 18:13:01 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		open_file(const char *path)
{
	int fd;

	if (access(path, F_OK) == 0)
	{
		if (access(path, R_OK) == 0)
		{
			fd = open(path, O_RDONLY);
			return (fd);
		}
	}
	return (-1);
}
