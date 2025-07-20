/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:44:58 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 15:11:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Philosopher main loop: eat, sleep, think until full or dead.
void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (sem_wait(philo->sim->start_sem) == -1)
		return (NULL);
	if (!set_lsem(&philo->sem, &philo->last_meal_time, get_time(MILLISECOND)))
		return (NULL);
	if (pthread_create(&philo->monitor, NULL, monitor_routine, philo))
		return (0);
	if (!adapt_fairness(philo))
		return (NULL);
	while (1)
	{
		if (philo->full == 1)
			break ;
		if (!eat(philo))
			return (NULL);
		if (!write_status(philo, SLEEP)
			|| !philo_usleep(philo->sim->stgs.sleep_time))
			return (NULL);
		if (!think(philo, 0))
			return (NULL);
	}
	return (NULL);
}

// Waits until a philo death or all philo full.
// In this case, kill all childs process.
void	*monitor_routine(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (check_death(philo) == 1)
		{
			write_status(philo, DEAD);
			sem_wait(philo->sim->output_sem);
			sem_post(philo->sim->end_sem);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}
