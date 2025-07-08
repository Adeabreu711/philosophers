/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:44:58 by alex              #+#    #+#             */
/*   Updated: 2025/07/08 17:20:03 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Loop until the philo died.
// (Special case for one fork in the table)
void	*philo_alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (sem_wait(philo->sim->start_sem) == -1)
		return (NULL);
	if (!set_lsem(&philo->sem, &philo->last_meal_time, get_time(MILLISECOND)))
		return (NULL);
	if (!write_status(philo, GRAB_F_FORK))
		return (NULL);
	while (1)
	{
		if (check_death(philo) == 1 && write_status(philo, DEAD))
		{
			sem_wait(philo->sim->output_sem);
			sem_post(philo->sim->end_sem);
			exit(1);
		}
	}
	return (NULL);
}

// Loop while the simulation is running and the philo isn't full.
// routine : eat, sleep, think.
void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (sem_wait(philo->sim->start_sem) == -1)
		return (NULL);
	if (!set_lsem(&philo->sem, &philo->last_meal_time, get_time(MILLISECOND)))
		return (NULL);
	if (!adapt_fairness(philo))
		return (NULL);
	while (1)
	{
		if (philo->full == 1)
			break ;
		if (check_death(philo) == 1 && write_status(philo, DEAD))
		{
			sem_wait(philo->sim->output_sem);
			sem_post(philo->sim->end_sem);
			exit(1);
		}
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
	t_sim	*sim;

	sim = data;
	if (sem_wait(sim->start_sem) == -1)
		return (NULL);
	sem_wait(sim->end_sem);
	kill_all_process(sim);
	return (NULL);
}
