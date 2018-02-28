/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_col_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 13:05:55 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/19 19:25:58 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_col_fd(char const *s, int fd, char *color)
{
	if (s)
	{
		ft_putstr(color);
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		ft_putstr(END_COL);
	}
}
