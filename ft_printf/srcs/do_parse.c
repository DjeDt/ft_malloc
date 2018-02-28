/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:05:29 by ddinaut           #+#    #+#             */
/*   Updated: 2018/02/15 15:01:14 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	get_precision(const char **format, t_opt *opt)
{
	(*format)++;
	opt->flags |= FLAG_PREC;
	if (**format < '1' || **format > '9')
	{
		opt->flags |= FLAG_ERR;
		while (ft_isdigit(**format))
			(*format)++;
		return ;
	}
	while (ft_isdigit(**format))
	{
		opt->precision = (opt->precision * 10) + **format - 48;
		(*format)++;
	}
}

void	get_width(const char **format, t_opt *opt)
{
	if (**format < '1' && **format > '9')
	{
		opt->flags |= FLAG_ERR;
		while (ft_isdigit(**format))
			(*format)++;
		return ;
	}
	while (ft_isdigit(**format))
	{
		opt->width = (opt->width * 10) + **format - 48;
		(*format)++;
	}
	opt->flags |= FLAG_LDC;
}

void	get_len_mod(const char **format, t_opt *opt)
{
	if (**format == 'h')
		opt->len_mod = MOD_H;
	else if (**format == 'l')
		opt->len_mod = MOD_L;
	else if (**format == 'j')
		opt->len_mod = MOD_J;
	else if (**format == 't')
		opt->len_mod = MOD_T;
	else if (**format == 'z')
		opt->len_mod = MOD_Z;
	(*format)++;
	if (**format == 'h' || **format == 'l')
	{
		if (**format == 'h')
			opt->len_mod = MOD_HH;
		else if (**format == 'l')
			opt->len_mod = MOD_LL;
		(*format)++;
	}
}

void	get_flags(const char **format, t_opt *opt)
{
	if (**format == '-')
		opt->flags |= FLAG_LEFT;
	else if (**format == '+')
		opt->flags |= FLAG_SIGN;
	else if (**format == '#')
		opt->flags |= FLAG_ALT;
	else if (**format == ' ')
	{
		opt->flags |= FLAG_SPACE;
		opt->prefix = ' ';
	}
	else if (**format == '0')
	{
		opt->flags |= FLAG_ZERO;
		opt->prefix = '0';
	}
	(*format)++;
}

int		do_parse(const char **format, va_list arg, t_core *core)
{
	init_opt(&core->opt);
	while (**format != '\0' && (oneof("-+ 0#", **format) == 1))
		get_flags(format, &core->opt);
	if (ft_isdigit(**format))
		get_width(format, &core->opt);
	if (**format == '.')
		get_precision(format, &core->opt);
	if (oneof("lhjtz", **format) == 1)
		get_len_mod(format, &core->opt);
	do_conv(**format, arg, core);
	return (1);
}
