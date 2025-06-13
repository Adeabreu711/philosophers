/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:50:23 by alex              #+#    #+#             */
/*   Updated: 2025/06/13 19:10:57 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

#include <sys/time.h>

typedef enum e_time_unit
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}t_time_unit;

long	get_time(t_time_unit unit);

#endif
