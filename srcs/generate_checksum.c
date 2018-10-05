/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_checksum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:02:25 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/05 13:26:01 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

unsigned long	hash_memory(unsigned char *str, size_t limit)
{
	unsigned int hash;

	hash = 0;
	while (limit--)
		hash += *str++;
	while (hash > 0xFFU)
		hash = (hash & 0xFFU) + ((hash >> 8) & 0xFFU);
	return (hash);
}

unsigned long	small_chunk_cheksum(void)
{
	t_area			*small;
	t_chunk			*tmp_chunk;
	unsigned long	cur_cksm;

	small = g_page.small;
	cur_cksm = 0;
	while (small != NULL)
	{
		cur_cksm += hash_memory((unsigned char*)small, AREA_SIZE);
		tmp_chunk = small->chunk;
		while (tmp_chunk != NULL)
		{
			cur_cksm += hash_memory((unsigned char*)tmp_chunk, HEADER_SIZE);
			tmp_chunk = tmp_chunk->next;
		}
		small = small->next;
	}
	return (cur_cksm);
}

unsigned long	medium_chunk_cheksum(void)
{
	t_area			*medium;
	t_chunk			*tmp_chunk;
	unsigned long	cur_cksm;

	medium = g_page.medium;
	cur_cksm = 0;
	while (medium != NULL)
	{
		cur_cksm += hash_memory((unsigned char*)medium, AREA_SIZE);
		tmp_chunk = medium->chunk;
		while (tmp_chunk != NULL)
		{
			cur_cksm += hash_memory((unsigned char*)tmp_chunk, HEADER_SIZE);
			tmp_chunk = tmp_chunk->next;
		}
		medium = medium->next;
	}
	return (cur_cksm);
}

unsigned long	bigger_chunk_cheksum(void)
{
	t_area			*small;
	unsigned long	cur_cksm;

	small = g_page.large;
	cur_cksm = 0;
	while (small != NULL)
	{
		cur_cksm += hash_memory((unsigned char*)small, AREA_SIZE);
		small = small->next;
	}
	return (cur_cksm);
}

unsigned long	generate_checksum(void)
{
	unsigned long	cksm;

	cksm = 0;
	cksm += small_chunk_cheksum();
	cksm += medium_chunk_cheksum();
	cksm += bigger_chunk_cheksum();
	if (CHECKSUM_DEBUG == ENABLE)
	{
		ft_putstr_fd("new generated cheksum is ", STDERR_FILENO);
		ft_puthex_fd(cksm, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (cksm);
}
