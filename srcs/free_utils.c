/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 19:48:12 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/06 19:53:21 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	merge_previous_chunk(t_chunk *prev, t_chunk *current)
{
	prev->size += (current->size + HEADER_SIZE);
	prev->next = current->next;
}

int		area_ready_to_free(t_area *area)
{
	int		percent_used;
	t_chunk	*tmp;

	tmp = area->chunk;
	while (tmp != NULL)
	{
		if (tmp->statut == USED)
			return (NOPE);
		tmp = tmp->next;
	}
	percent_used = (area->size_used * 100) / area->size_max;
	if (percent_used > PERCENT_ALLOWED)
		return (SUCCESS);
	return (NOPE);
}
