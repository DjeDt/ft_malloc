/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:34:34 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/20 17:58:50 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void		do_long(va_list arg, char c, t_core *core)
{
	core->opt.len_mod = MOD_L;
	if (c == 'D')
		do_int(arg, 'd', core);
	else if (c == 'O')
		do_unsign(arg, 'o', core);
	else if (c == 'U')
		do_unsign(arg, 'u', core);
}
