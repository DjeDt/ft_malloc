/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_col.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:35:37 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/25 16:35:38 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_col(const char *str, char *color)
{
	if (str)
	{
		ft_putstr(color);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		ft_putstr(END_COL);
	}
}
