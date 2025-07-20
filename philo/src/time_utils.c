/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:49:24 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 15:30:39 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/time.h"
#include <stdio.h>

// Get time int the given unit.
long	get_time(t_time_unit unit)
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
