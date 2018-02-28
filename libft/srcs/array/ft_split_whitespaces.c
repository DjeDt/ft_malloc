/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 11:15:00 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:46:18 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		delimiteurs(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\n'))
		return (1);
	return (0);
}

static int		ft_count(char *str)
{
	int i;

	i = 0;
	while (!(delimiteurs(str[i])) && str[i])
		i++;
	return (i);
}

static int		nbr_mots(char *str)
{
	int i;
	int nombremot;

	i = 0;
	nombremot = 0;
	while (str[i])
	{
		while ((delimiteurs(str[i])))
			i++;
		if (str[i] != '\0')
		{
			while ((!delimiteurs(str[i])) && str[i])
				i++;
			nombremot++;
		}
	}
	return (nombremot);
}

char			**ft_split_whitespaces(char *str)
{
	int		i;
	int		j;
	int		taille;
	int		nbmot;
	char	**tab;

	i = 0;
	j = 0;
	taille = 0;
	nbmot = nbr_mots(str);
	if (!(tab = (char**)malloc(sizeof(char*) * (nbmot + 1))))
		return (NULL);
	while (j < nbmot)
	{
		while ((delimiteurs(str[i])))
			i++;
		taille = ft_count(&str[i]);
		tab[j] = ft_strndup(str + i, taille);
		i += taille;
		j++;
	}
	tab[j] = 0;
	return (tab);
}
