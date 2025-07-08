/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:50:23 by alex              #+#    #+#             */
/*   Updated: 2025/07/02 16:18:15 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include <sys/time.h>

typedef enum e_time_unit
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_unit;

long	get_time(t_time_unit unit);

#endif
