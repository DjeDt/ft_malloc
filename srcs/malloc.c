/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/21 19:11:02 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		check_small_area(void)
{
	size_t	total;

	if (g_page.small == NULL)
	{
		total = TINY_SIZE * getpagesize();
		g_page.small = mmap(NULL, total + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (g_page.small == MAP_FAILED)
		{
			ft_putendl_fd("allocation error. not enought space left.", 2);
			return (ERROR);
		}
		g_page.small->size_used = 0;
		g_page.small->size_max = total;
		g_page.small->map = g_page.small + AREA_SIZE;
		g_page.small->chunk = NULL;
		g_page.small->next = NULL;
	}
	return (SUCCESS);
}

int		check_medium_area(void)
{
	size_t	total;

	if (g_page.medium == NULL)
	{
		total = MEDIUM_SIZE * getpagesize();
		g_page.medium = mmap(NULL, total + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (g_page.medium == MAP_FAILED)
		{
			ft_putendl_fd("allocation error. not enought space left.", 2);
			return (ERROR);
		}
		g_page.medium->size_used = 0;
		g_page.medium->size_max = total;
		g_page.medium->map = g_page.medium + AREA_SIZE;
		g_page.medium->chunk = NULL;
		g_page.medium->next = NULL;
	}
	return (SUCCESS);
}

int		create_arena(size_t size)
{
	int	ret;

	ret = SUCCESS;
	if (size <= TINY_SIZE)
		ret = check_small_area();
	else if (size <= MEDIUM_SIZE)
		ret = check_medium_area();
	return (ret);
}

void	*malloc(size_t size)
{
	void	*ret;

	ft_putstr("[malloc] : ");
	ft_putnbr(size);
	ft_putchar('\n');

	if (size == 0)
		return (malloc(16));
	if (create_arena(size) != SUCCESS)
		return (NULL);
	ret = push_chunk_to_area(size);
	return (ret);
}
