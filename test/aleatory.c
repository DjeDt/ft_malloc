/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aleatory.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:11:17 by ddinaut           #+#    #+#             */
/*   Updated: 2019/02/28 19:06:43 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "debug.h"
#include "libft.h"
#include "printf.h"
#include <sys/wait.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

/* Returns an integer in the range [0, n).
 *
 * Uses rand(), and so is affected-by/affects the same seed.
 */
int randint(int n)
{
	if ((n - 1) == RAND_MAX)
	{
		return rand();
	}
	else
	{
		// Supporting larger values for n would requires an even more
		// elaborate implementation that combines multiple calls to rand()
		assert (n <= RAND_MAX);

		// Chop off all of the values that would cause skew...
		int end = RAND_MAX / n; // truncate skew
		assert (end > 0);
		end *= n;

		// ... and ignore results from rand() that fall above that limit.
		// (Worst case the loop condition should succeed 50% of the time,
		// so we can expect to bail out of this loop pretty quickly.)
		int r;
		while ((r = rand()) >= end);

		return (r % n);
	}
}

void	aleatory_test(int limit)
{
	int aleat_func;
	int aleat_size;
	int aleat_size2;
	int bkp;
	char *ptr[limit];

	bkp = 0;
    srand(time(NULL));
	ft_putstr("limit = ");
	ft_putnbr(limit);
	ft_putchar('\n');
	for (int count = 0 ; count < limit ; count++)
	{
		aleat_func = randint(4);
		aleat_size = randint(7000);
		ft_putnbr(count);
		ft_putstr(": ");
		if (aleat_func == 0) // malloc()
		{
			ft_putstr("malloc : ");
			ft_putnbr(aleat_size);
			ptr[bkp] = malloc(aleat_size);
			bkp++;
		}
		else if (aleat_func == 1) // free()
		{
			ft_putstr("free");
			free(ptr[bkp]);
			if (bkp > 0)
				bkp--;
		}
		else if (aleat_func == 2) // realloc
		{
			ft_putstr("realloc : ");
			ft_putnbr(aleat_size);
			ptr[bkp] = realloc(ptr[bkp], aleat_size);
			bkp++;
		}
		else if (aleat_func == 3) // calloc
		{
			ft_putstr("calloc : ");
			aleat_size2 = randint(10);
			ft_putnbr(aleat_size);
			ft_putstr(" * ");
			ft_putnbr(aleat_size2);
			ptr[bkp] = calloc(aleat_size, aleat_size2);
			bkp++;
		}
		ft_putchar('\n');
	}

	while (limit > 0)
	{
		free(ptr[limit]);
		limit--;
	}
}

int main(int ac, char **av)
{
	if (ac == 1)
	{
		ft_putendl("error: need iteration num");
		return (0);
	}
	aleatory_test(atoi(av[1]));
	return (0);
}
