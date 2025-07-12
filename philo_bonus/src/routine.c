/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:44:58 by alex              #+#    #+#             */
/*   Updated: 2025/07/09 15:53:29 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Loop for the special case with one philosopher and one fork.
// The philosopher grabs a fork, waits, and dies eventually.
void	*philo_alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (sem_wait(philo->sim->start_sem) == -1)
		return (NULL);
	if (!set_lsem(&philo->sem, &philo->last_meal_time, get_time(MILLISECOND)))
		return (NULL);
	if (!write_status(philo, GRAB_FORK))
		return (NULL);
	while (1)
	{
		if (check_death(philo) == 1)
			return (send_death_report(philo), NULL);
	}
	return (NULL);
}

// Philosopher main loop: eat, sleep, think until full or dead.
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
		if (check_death(philo) == 1)
			return (send_death_report(philo), NULL);
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
	t_sim	*sim;

	sim = data;
	if (sem_wait(sim->start_sem) == -1)
		return (NULL);
	if (sem_wait(sim->end_sem) == -1)
		return (NULL);
	kill_all_child(sim);
	return (NULL);
}
