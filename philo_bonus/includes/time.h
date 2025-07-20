/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:50:23 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 15:31:23 by alde-abr         ###   ########.fr       */
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
