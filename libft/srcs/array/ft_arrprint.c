/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 12:52:11 by ddinaut           #+#    #+#             */
/*   Updated: 2017/04/25 17:06:44 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrprint(char **tab)
{
	size_t	count;

	count = -1;
	if (tab == NULL)
		return ;
	while (tab[++count] != NULL)
		ft_putendl(tab[count]);
}
