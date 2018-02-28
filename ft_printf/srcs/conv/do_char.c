/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:14:20 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/20 14:55:05 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	level_2(wchar_t ch, char **to_add, int *count)
{
	(*to_add)[(*count)++] = ((ch >> 6) + 0xC0);
	(*to_add)[(*count)++] = ((ch & 0x3F) + 0x80);
}

void	level_3(wchar_t ch, char **to_add, int *count)
{
	(*to_add)[(*count)++] = ((ch >> 12) + 0xE0);
	(*to_add)[(*count)++] = (((ch >> 6) & 0x3F) + 0x80);
	(*to_add)[(*count)++] = ((ch & 0x3F) + 0x80);
}

void	level_4(wchar_t ch, char **to_add, int *count)
{
	(*to_add)[(*count)++] = ((ch >> 18) + 0xF0);
	(*to_add)[(*count)++] = (((ch >> 12) & 0x3F) + 0x80);
	(*to_add)[(*count)++] = (((ch >> 6) & 0x3F) + 0x80);
	(*to_add)[(*count)++] = ((ch & 0x3F) + 0x80);
}

void	char_to_str(wchar_t ch, char **to_add, size_t *bytes)
{
	int count;

	count = 0;
	if (ch <= 0x7F)
		(*to_add)[count++] = ch;
	else if (ch <= 0x7FF)
		level_2(ch, to_add, &count);
	else if (ch <= 0xFFFF)
		level_3(ch, to_add, &count);
	else if (ch <= 0x10FFFF)
		level_4(ch, to_add, &count);
	(*bytes) = count;
	while (count < 5)
		(*to_add)[count++] = '\0';
}

void	do_char(va_list arg, char c, t_core *core)
{
	wchar_t	ch;
	char	*to_add;

	ch = 0;
	to_add = NULL;
	if (!(to_add = (char*)malloc(sizeof(char) * 5)))
		return ;
	if (c == 'c')
	{
		if (core->opt.len_mod == MOD_L)
			ch = (wint_t)va_arg(arg, wint_t);
		else
			ch = (char)va_arg(arg, int);
	}
	else if (c == 'C')
		ch = (wint_t)va_arg(arg, wint_t);
	else
		ch = c;
	char_to_str(ch, &to_add, &core->opt.len_cpy);
	concat_char(&to_add, core);
	final_concat(core, to_add);
}
