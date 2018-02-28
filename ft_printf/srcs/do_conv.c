/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:23:58 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/20 18:18:20 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	normal_char(char c, t_core *core)
{
	char	*to_add;

	init_opt(&core->opt);
	if (!(to_add = (char*)malloc(sizeof(char) * 5)))
		return ;
	char_to_str(c, &to_add, &core->opt.len_cpy);
	final_concat(core, to_add);
}

void	do_conv(char c, va_list arg, t_core *core)
{
	if (oneof("di", c))
		do_int(arg, c, core);
	else if (oneof("cC", c))
		do_char(arg, c, core);
	else if (oneof("ouxX", c))
		do_unsign(arg, c, core);
	else if (oneof("sSp", c))
		do_ptr(arg, c, core);
	else if (oneof("DOU", c))
		do_long(arg, c, core);
	else if (c != '\0')
		do_char(arg, c, core);
}
