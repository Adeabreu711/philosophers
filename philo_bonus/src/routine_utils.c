/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:03:45 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 14:31:26 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Create a time interval between pair philos and odds
// Returns 1 on success, 0 on failure.
int	adapt_fairness(t_philo *philo)
{
	if (philo->sim->stgs.philo_nb % 2 == 0)
	{
		if (philo->id % 2 == 0)
		{
			if (!philo_usleep(3e4))
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

// Check if the philosopher has exceeded time to die.
// Returns: -1 (error), 0 (alive), 1 (dead).
int	check_death(t_philo *philo)
{
	long	time;
	long	lst_meal_t;

	if (get_isem(&philo->sem, &philo->full) == 1)
		return (0);
	lst_meal_t = get_lsem(&philo->sem, &philo->last_meal_time);
	time = get_time(MILLISECOND);
	if (!time || !lst_meal_t)
		return (-1);
	if ((time - lst_meal_t) > philo->sim->stgs.die_time / 1e3)
		return (1);
	return (0);
}

// Report philosopher death and notify end of simulation.
// Returns 1 on success, 0 on failure.
int	send_death_report(t_philo *philo)
{
	if (!write_status(philo, DEAD))
		return (0);
	if (sem_wait(philo->sim->output_sem))
		return (0);
	if (sem_post(philo->sim->end_sem))
		return (0);
	return (1);
}

// Kill all philosopher processes and release output lock.
// Returns 1 on success, 0 on failure.
int	kill_all_child(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->stgs.philo_nb)
	{
		if (kill(sim->philo[i].pid, SIGKILL))
			continue ;
	}
	if (sem_post(sim->output_sem) == -1)
		return (0);
	return (1);
}
