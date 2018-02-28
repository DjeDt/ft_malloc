/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_final.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 19:29:28 by ddinaut           #+#    #+#             */
/*   Updated: 2017/12/20 11:16:02 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	final_concat(t_core *core, void *to_add)
{
	int		len;
	char	*new;

	new = NULL;
	len = (core->bytes + core->opt.len_cpy);
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return ;
	ft_memcpy(new, core->final, core->bytes);
	ft_memcpy(&new[core->bytes], to_add, core->opt.len_cpy);
	new[len] = '\0';
	core->bytes += core->opt.len_cpy;
	if (core->final)
		free(core->final);
	core->final = new;
	if (to_add)
		free(to_add);
}
