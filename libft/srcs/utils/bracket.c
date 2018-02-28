/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:42:35 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:48:01 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		compare(char x, char y)
{
	if (x == '[' && y == ']')
		return (1);
	else if (x == '{' && y == '}')
		return (1);
	else if (x == '(' && y == ')')
		return (1);
	return (0);
}

int		bracket(char *s)
{
	char	stack[4096];
	char	*pt;

	ft_bzero(stack);
	pt = stack;
	while ((*s))
	{
		if ((*s) == '[' || (*s) == '{' || (*s) == '(')
		{
			pt++;
			*pt = *s;
		}
		else if ((*s) == ']' || (*s) == '}' || (*s) == ')')
		{
			if (compare((*pt), (*s)) == 0)
				return (0);
			*pt-- = 0;
		}
		s++;
	}
	if (pt == stack)
		return (1);
	return (0);
}
