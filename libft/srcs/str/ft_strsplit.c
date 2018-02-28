/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 15:42:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:37:14 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		nbr_mots(const char *str, char c)
{
	int i;
	int nombremot;

	i = 0;
	nombremot = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
		{
			nombremot++;
			while ((str[i] != '\0') && (str[i] != c))
				i++;
		}
	}
	return (nombremot);
}

char			**ft_strsplit(const char *s, char c)
{
	int		i;
	int		j;
	int		taille;
	int		nbmot;
	char	**ret;

	i = 0;
	j = -1;
	taille = 0;
	if (s == NULL)
		return (NULL);
	nbmot = nbr_mots(s, c);
	if (!(ret = (char**)malloc(sizeof(char*) * nbmot + 1)))
		return (NULL);
	while (++j < nbmot)
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		taille = ft_strnlen(s + i, c);
		ret[j] = ft_strndup(s + i, taille);
		i += taille;
	}
	ret[j] = NULL;
	return (ret);
}
