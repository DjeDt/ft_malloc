/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:55:08 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/15 16:02:06 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	get_power_of_2(size_t size)
{
	size_t count;

	count = 0;
	if (size && !(size & (size - 1)))
		return (size);
	while (size != 0)
	{
		size  >>= 1;
		count += 1;
	}
	return (1 << count);
}

void	get_sys_info(void)
{
	int ret;
	struct rlimit test;

	ft_putstr("core limit :\n");
	ret = getrlimit(RLIMIT_CORE, &test);
	ft_putnbr(test.rlim_cur);
	ft_putchar('\n');
	ft_putnbr(test.rlim_max);
	ft_putchar('\n');
	ft_putchar('\n');

	ft_putendl("limit stack :");
	ret = getrlimit(RLIMIT_STACK, &test);
	ft_putnbr(test.rlim_cur);
	ft_putchar('\n');
	ft_putnbr(test.rlim_max);
	ft_putchar('\n');
	ft_putchar('\n');

	ft_putendl("limit nofile :");
	ret = getrlimit(RLIMIT_NOFILE, &test);
	ft_putnbr(test.rlim_cur);
	ft_putchar('\n');
	ft_putnbr(test.rlim_max);
	ft_putchar('\n');

	ft_putendl("\ngetpagesize :");
	ft_putnbr(getpagesize());
	ft_putchar('\n');
}

void	print_large(t_area **large)
{
	t_area *tmp;

	tmp = (*large);
	if (tmp)
	{
		while (tmp)
		{
			printf("chunk addr = %p\n", tmp->chunk);
			printf("size = %zu\n", tmp->chunk->size);
			printf("data addr = %p\n", tmp->chunk->data);
			printf("statut = %d\n", tmp->chunk->statut);
			if (tmp->next)
			{
				printf("[next node]\n");
				tmp = tmp->next;
			}
			else
			{
				printf("end print large one\n");
				break ;
			}
		}
	}
	else
		ft_putendl("empty list");
}

void	print_allocated_chunk(t_chunk **base)
{
	t_chunk	*tmp;

	tmp = (*base);
	if (tmp)
	{
		printf("[BEGIN ALLOCATED CHUNK] :\n");
		while (tmp)
		{
			printf("[node addr] = %p\n", tmp);
			printf("[size] %zu\n", tmp->size);
			printf("[data addr] %p\n", tmp->data);
			printf("[statut] %d\n", tmp->statut);
			if (tmp->next)
			{
				ft_putstr("\n[next node] :\n");
				tmp = tmp->next;
			}
			else
			{
				ft_putstr("\n[ENDING ALLOCATED CHUNK]\n");
				break ;
			}
		}
	}
	else
		ft_putendl("empty list");
}
