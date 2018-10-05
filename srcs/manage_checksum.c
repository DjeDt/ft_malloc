/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_checksum.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:52:04 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/05 17:03:59 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		compare_checksum(void)
{
	if (ENABLE_CHECKSUM == ENABLE)
	{
		if (g_page.checksum != generate_checksum())
		{
			ft_putendl_fd("error, hash differs, corrupted data", STDERR_FILENO);
			return (ERROR);
		}
		return (SUCCESS);
	}
	return (NOPE);
}

int		generate_new_checksum(void)
{
	if (ENABLE_CHECKSUM == ENABLE)
	{
		g_page.checksum = generate_checksum();
		return (SUCCESS);
	}
	return (NOPE);
}
