/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:32:41 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:37:29 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	found_one(char c, const char *delim)
{
	int i;

	i = 0;
	if (c == 0)
		return (0);
	while (delim[i] != '\0')
	{
		if (delim[i] == c)
			return (0);
		i++;
	}
	return (-1);
}

static int	count_word(const char *str, const char *delim)
{
	int	i;
	int count;

	i = -1;
	count = 0;
	while (str[++i] != '\0')
	{
		if ((found_one(str[i], delim) == -1) && \
			(found_one(str[i + 1], delim) == 0))
			count++;
	}
	return (count);
}

char		**ft_strtok(const char *str, const char *delim)
{
	int		j;
	int		k;
	int		count;
	char	**tab;

	if (str == NULL)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * (count_word(str, delim) + 1))))
		return (NULL);
	j = -1;
	k = 0;
	count = -1;
	while (str[++count] != '\0')
	{
		found_one(str[count], delim) == -1 ? k++ : 0;
		if ((found_one(str[count], delim) == -1) && \
			(found_one(str[count + 1], delim) == 0))
		{
			tab[++j] = ft_strndup(&str[count - (k - 1)], k);
			k = 0;
		}
	}
	tab[++j] = NULL;
	return (tab);
}
