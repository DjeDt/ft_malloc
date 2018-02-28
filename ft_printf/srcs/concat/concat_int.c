/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:43:14 by ddinaut           #+#    #+#             */
/*   Updated: 2017/12/28 16:49:49 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	int_alter(long long int i, char **to_add, t_opt opt)
{
	char	*new;

	new = NULL;
	if ((opt.flags & FLAG_SPACE) && (i >= 0) && ((opt.flags & FLAG_SIGN) == 0))
	{
		new = ft_strjoin(" ", (*to_add));
		free((*to_add));
		(*to_add) = new;
		opt.flags &= ~FLAG_SPACE;
	}
	else if ((opt.flags & FLAG_SIGN) && (i >= 0))
	{
		new = ft_strjoin("+", (*to_add));
		free((*to_add));
		(*to_add) = new;
		opt.flags &= ~FLAG_SIGN;
	}
}

void	int_width(long long int i, char **to_add, t_opt opt)
{
	int		len;
	char	*new;
	char	*padding;

	padding = NULL;
	len = opt.width - ft_strlen((*to_add));
	(check_int_exception(i, opt) > 0) && (i >= 0) ? len -= 1 : 0;
	if (len <= 0)
		return ;
	if (opt.flags & FLAG_LEFT)
	{
		int_alter(i, to_add, opt);
		padding = create_padding(len, ' ');
		new = ft_strjoin((*to_add), padding);
	}
	else
	{
		opt.prefix == ' ' ? int_alter(i, to_add, opt) : 0;
		padding = create_padding(len, opt.prefix);
		new = ft_strjoin(padding, (*to_add));
		opt.prefix != ' ' ? int_alter(i, &new, opt) : 0;
	}
	free((*to_add));
	(*to_add) = new;
	ft_strdel(&padding);
}

void	int_precision(char **to_add, long long int i, t_opt opt)
{
	int		len;
	char	*new;
	char	*padding;

	new = NULL;
	padding = NULL;
	if (opt.precision <= 0 && i == 0)
	{
		(*to_add)[0] = '\0';
		return ;
	}
	len = opt.precision - ft_strlen((*to_add));
	if (i < 0)
		len += 1;
	if (len > 0)
	{
		padding = create_padding(len, '0');
		new = ft_strjoin(padding, (*to_add));
		free((*to_add));
		(*to_add) = new;
		ft_strdel(&padding);
	}
}

void	concat_int(long long int i, char c, char **to_add, t_core *core)
{
	(void)c;
	if (core->opt.flags & FLAG_PREC)
	{
		int_precision(to_add, i, core->opt);
		if (core->opt.flags & FLAG_LDC)
		{
			core->opt.prefix = ' ';
			int_width(i, to_add, core->opt);
		}
	}
	else if (core->opt.flags & FLAG_LDC)
		int_width(i, to_add, core->opt);
	else
		int_alter(i, to_add, core->opt);
	if (i < 0)
		move_sign(to_add);
	core->opt.len_cpy = ft_strlen((*to_add));
}
