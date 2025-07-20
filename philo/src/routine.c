/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:44:58 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 15:30:14 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Loop until the philo died.
// (Special case for one fork in the table)
void	*philo_alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_start(philo->last_meal_time);
	if (!set_lmtx(&philo->mtx, &philo->last_meal_time, get_time(MILLISECOND)))
		return (NULL);
	if (!write_status(philo, GRAB_F_FORK))
		return (NULL);
	while (get_imtx(&philo->sim->mtx, &philo->sim->end_sim) == -1)
		usleep(200);
	return (NULL);
}

// Loop while the simulation is running and the philo isn't full.
// routine : eat, sleep, think.
void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_start(philo->last_meal_time);
	if (!set_lmtx(&philo->mtx, &philo->last_meal_time, get_time(MILLISECOND)))
		return (NULL);
	if (!adapt_fairness(philo))
		return (NULL);
	while (get_imtx(&philo->sim->mtx, &philo->sim->end_sim) == -1)
	{
		if (philo->full == 1)
			break ;
		eat(philo);
		if (!write_status(philo, SLEEP)
			|| !philo_usleep(philo->sim->stgs.sleep_time, philo->sim))
			return (NULL);
		think(philo, 0);
	}
	return (NULL);
}

// Loop while the simulation is running and all philos are alive.
// If a philo died, show is "DEAD" status and stop the simulation.
void	*monitor_routine(void *data)
{
	int		i;
	t_sim	*sim;

	i = -1;
	sim = data;
	wait_start(sim->start_time);
	while (get_imtx(&sim->mtx, &sim->end_sim) == -1)
	{
		while (++i < sim->stgs.philo_nb)
		{
			if (check_death(&sim->philo[i]) == 1)
			{
				if (!set_imtx(&sim->mtx, &sim->end_sim, 1))
					return (NULL);
				write_status(&sim->philo[i], DEAD);
				break ;
			}
		}
		usleep(100);
		i = -1;
	}
	return (NULL);
}
