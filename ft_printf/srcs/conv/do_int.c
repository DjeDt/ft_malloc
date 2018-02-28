/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:15:44 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/20 17:51:04 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	init_int_value(unsigned long long int *val, long long int value, \
					int base, int *neg)
{
	(*neg) = 0;
	if (value < 0)
	{
		if (base == 10)
			(*neg) = 1;
		(*val) = value * (-1);
	}
	else
		(*val) = value;
}

char		*convert_int(long long int val, int base)
{
	int						neg;
	int						count;
	char					*ret;
	const char				*str;
	unsigned long long int	value;

	init_int_value(&value, val, base, &neg);
	count = nbr_len(value, base) + neg;
	str = "0123456789abcdef";
	if (!(ret = (char*)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	ret[count] = '\0';
	while (count-- > neg)
	{
		ret[count] = str[(value % base)];
		value /= base;
	}
	neg == 1 ? ret[0] = '-' : 0;
	return (ret);
}

int			check_int_exception(long long int i, t_opt opt)
{
	if ((opt.flags & FLAG_SPACE) && (i >= 0) && ((opt.flags & FLAG_SIGN) == 0))
		return (1);
	else if ((opt.flags & FLAG_SIGN) && (i >= 0))
		return (2);
	return (0);
}

void		do_int_exeption(long long int i, t_opt opt, char **to_add)
{
	if (check_int_exception(i, opt) == 1)
		(*to_add) = ft_strjoin_fr(" ", (*to_add));
	else if (check_int_exception(i, opt) == 2)
		(*to_add) = ft_strjoin_fr("+", (*to_add));
}

void		do_int(va_list arg, char c, t_core *core)
{
	long long int	i;
	char			*to_add;

	if (core->opt.len_mod == MOD_L)
		i = (long)va_arg(arg, long long int);
	else if (core->opt.len_mod == MOD_LL)
		i = (long long)va_arg(arg, long long int);
	else if (core->opt.len_mod == MOD_H)
		i = (short int)va_arg(arg, long long int);
	else if (core->opt.len_mod == MOD_HH)
		i = (signed char)va_arg(arg, long long int);
	else if (core->opt.len_mod == MOD_J)
		i = (intmax_t)va_arg(arg, long long int);
	else if (core->opt.len_mod == MOD_T)
		i = (ptrdiff_t)va_arg(arg, long long int);
	else if (core->opt.len_mod == MOD_Z)
		i = (size_t)va_arg(arg, long long int);
	else
		i = (int)va_arg(arg, long long int);
	to_add = convert_int(i, 10);
	concat_int(i, c, &to_add, core);
	final_concat(core, to_add);
}
