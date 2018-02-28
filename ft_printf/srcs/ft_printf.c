/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:04:41 by ddinaut           #+#    #+#             */
/*   Updated: 2018/02/27 15:32:47 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	init_opt(t_opt *opt)
{
	opt->flags = 0;
	opt->type = 0;
	opt->prefix = ' ';
	opt->width = 0;
	opt->precision = 0;
	opt->len_mod = 0;
	opt->len_cpy = 0;
}

void	init_core(t_core *core)
{
	core->bytes = 0;
	core->final = NULL;
}

int		begin_parse(const char *format, va_list arg)
{
	t_core	core;

	init_core(&core);
	while ((*format) != '\0')
	{
		if ((*format) == '%')
		{
			format++;
			if (*format != '\0')
				do_parse(&format, arg, &core);
			else
			{
				format--;
				normal_char(*format, &core);
			}
		}
		else
			normal_char(*format, &core);
		format++;
	}
	if (write(1, core.final, core.bytes) == -1)
		return (-1);
	ft_strdel((char**)&core.final);
	return (core.bytes);
}

int		ft_printf(const char *restrict format, ...)
{
	int		ret;
	va_list	arg;
	char	*fmt;

	va_start(arg, format);
	fmt = (char*)format;
	ret = begin_parse(fmt, arg);
	va_end(arg);
	return (ret);
}
