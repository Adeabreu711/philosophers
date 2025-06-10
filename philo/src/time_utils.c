/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:49:24 by alex              #+#    #+#             */
/*   Updated: 2025/06/10 21:59:12 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/time.h"
#include <stdio.h>

long	get_time(time_unit unit)
{
	struct timeval	tmvl;
	long			micro;

	if (gettimeofday(&tmvl, 0))
		return (0);
	micro = (tmvl.tv_sec * 1e6) + tmvl.tv_usec;
	if (unit == SECOND)
		return (micro / (long)1e6);
	if (unit == MILLISECOND)
		return (micro / (long)1e3);
	if (unit == MICROSECOND)
			return (micro);
	return (-1);
}
