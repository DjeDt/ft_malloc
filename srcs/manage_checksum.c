/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_checksum.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:52:04 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/18 12:31:03 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		compare_checksum(void)
{
	if (ENABLE_CHECKSUM == ENABLE)
	{
		if (g_page.checksum != generate_checksum())
		{
			ft_putendl_fd(\
				"Error: hash differs, corrupted metadata", STDERR_FILENO);
			if (ENABLE_CHEKSUM_ABORT == ENABLE)
			{
				ft_putendl_fd(\
					"Fatal error: abort current program", STDERR_FILENO);
				exit(EXIT_FAILURE);
			}
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
