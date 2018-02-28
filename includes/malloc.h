/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:41:23 by ddinaut           #+#    #+#             */
/*   Updated: 2018/02/28 20:21:56 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MALLOC_H
# define	MALLOC_H

#include <sys/mman.h>
#include <unistd.h>

#include "../libft/includes/libft.h"
#include "../ft_printf/includes/printf.h"

void	*malloc(size_t size);

#endif
