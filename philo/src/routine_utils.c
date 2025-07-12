/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:03:45 by alex              #+#    #+#             */
/*   Updated: 2025/07/09 21:46:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Loop until the given threads_ready value is reached.
// Threads_ready == 0 is an error.
int	synchronize_threads(t_sim *sim, int value)
{
	if (!get_imtx(&sim->mtx, &sim->threads_ready))
		return (0);
	while (get_imtx(&sim->mtx, &sim->threads_ready) < value)
		continue ;
	return (1);
}

// Create a time interval between pair and odds philos
int	adapt_fairness(t_philo *philo)
{
	if (philo->sim->stgs.philo_nb % 2 == 0)
	{
		if (philo->id % 2 == 0)
		{
			if (!philo_usleep(3e4, philo->sim))
				return (0);
		}
	}
	else
	{
		if (philo->id % 2)
		{
			if (!think(philo, 1))
				return (0);
		}
	}
	return (1);
}

// Check if the time elapsed after the philo last meal
// is superior to the death time.
// Return : -1 (error), 0 (not dead), 1 (dead)
int	check_death(t_philo *philo)
{
	long	time;
	long	lst_meal_t;

	if (get_imtx(&philo->mtx, &philo->full) == 1)
		return (0);
	lst_meal_t = get_lmtx(&philo->mtx, &philo->last_meal_time);
	time = get_time(MILLISECOND);
	if (!time || !lst_meal_t)
		return (-1);
	if ((time - lst_meal_t) > philo->sim->stgs.die_time / 1e3)
		return (1);
	return (0);
}
