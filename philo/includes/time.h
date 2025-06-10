/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:50:23 by alex              #+#    #+#             */
/*   Updated: 2025/06/10 21:59:17 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

#include <sys/time.h>

typedef enum time_unit
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}time_unit;

long	get_time(time_unit unit);

#endif
