/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:05:38 by alex              #+#    #+#             */
/*   Updated: 2025/07/08 14:04:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Wait with precision using usleep in a more accurate way.
// Usleep is used until a treshold limit, after that CPU is used (busy waiting).
int	philo_usleep(long usec, t_sim *sim)
{
	long	start;
	long	rem;

	start = get_time(MICROSECOND);
	while (1)
	{
		rem = usec - (get_time(MICROSECOND) - start);
		if (rem <= 0)
			break ;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			continue ;
	}
	return (1);
}

// Print the "GRAP FORK" and "EAT" status of the given philo if not full.
// Uptate the philo eat counter and last meal time.
// Lock and unlock the simulation main mutex.
int	eat(t_philo *philo)
{
	if (sem_wait(philo->sim->forks_sem) == -1
		|| !write_status(philo, GRAB_F_FORK))
		return (0);
	if (sem_wait(philo->sim->forks_sem) == -1
		|| !write_status(philo, GRAB_S_FORK))
		return (0);
	if (!set_lsem(&philo->sem, &philo->last_meal_time, get_time(MILLISECOND))
		|| !write_status(philo, EAT))
		return (0);
	philo->eat_count++;
	if (!philo_usleep(philo->sim->stgs.eat_time, philo->sim))
		return (0);
	if (philo->sim->stgs.max_meals > 0
		&& philo->eat_count == philo->sim->stgs.max_meals)
	{
		if (!set_isem(&philo->sem, &philo->full, 1))
			return (0);
	}
	if (sem_post(philo->sim->forks_sem) == -1)
		return (0);
	if (sem_post(philo->sim->forks_sem) == -1)
		return (0);
	return (1);
}

// Print the "THINK" status of the given philo.
int	think(t_philo *philo, int init)
{
	int	think_time;

	if (!init)
	{
		if (!write_status(philo, THINK))
			return (0);
	}
	if (philo->id % 2 == 0 || philo->sim->stgs.philo_nb % 2 == 0)
		return (1);
	think_time = philo->sim->stgs.eat_time * 2 - philo->sim->stgs.sleep_time;
	if (think_time < 0)
		return (1);
	if (!philo_usleep(0.25 * think_time, philo->sim))
		return (0);
	return (1);
}

// Print the status of the given philo if the simulation is running.
// Lock and unlock the output mutex.
int	write_status(t_philo *philo, t_status status)
{
	int		end_sim;
	long	time;

	if (philo->full)
		return (1);
	if (sem_wait(philo->sim->output_sem) == -1)
		return (0);
	time = get_time(MILLISECOND)
		- get_lsem(philo->sim->global_sem, &philo->sim->start_time);
	if (time < 0)
		return (sem_post(philo->sim->output_sem), 0);
	if ((status == GRAB_F_FORK || status == GRAB_S_FORK))
		printf("%li %i has taken a fork\n", time, philo->id);
	else if (status == EAT)
		printf("%li %i is eating\n", time, philo->id);
	else if (status == SLEEP )
		printf("%li %i is sleeping\n", time, philo->id);
	else if (status == THINK)
		printf("%li %i is thinking\n", time, philo->id);
	else if (status == DEAD)
		printf("%li %i died\n", time, philo->id);
	if (sem_post(philo->sim->output_sem) == -1)
		return (0);
	return (1);
}
