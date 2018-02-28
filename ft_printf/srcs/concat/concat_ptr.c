/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 10:20:25 by ddinaut           #+#    #+#             */
/*   Updated: 2017/12/28 14:41:53 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ptr_width(char **add, t_opt opt)
{
	int		len;
	char	*new;
	char	*padding;

	new = NULL;
	padding = NULL;
	len = opt.width - ft_strlen((*add));
	if (len > 0)
	{
		padding = create_padding(len, opt.prefix);
		if (opt.flags & FLAG_LEFT)
			new = ft_strjoin((*add), padding);
		else
			new = ft_strjoin(padding, (*add));
		if (padding)
			free(padding);
		free(*add);
		(*add) = new;
	}
}

void	ptr_precision(char **add, t_opt opt)
{
	int len;

	len = ft_strlen((*add));
	if (opt.precision < len)
		while ((*add)[opt.precision] != '\0' && opt.precision < len)
		{
			(*add)[opt.precision] = '\0';
			opt.precision++;
		}
}

void	concat_ptr(char **add, t_core *core)
{
	if (core->opt.flags & FLAG_PREC)
	{
		ptr_precision(add, core->opt);
		if (core->opt.flags & FLAG_LDC)
			ptr_width(add, core->opt);
	}
	else
	{
		if (core->opt.flags & FLAG_LDC)
			ptr_width(add, core->opt);
	}
	core->opt.len_cpy = ft_strlen((*add));
}
