/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:05:38 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 15:32:00 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Sleep with high precision.
// Uses usleep until a low threshold, then busy-waits.
int	philo_usleep(long usec)
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

// Philosopher takes two forks, eats, updates state, then releases forks.
// Updates last_meal_time and increments eat_count.
// Marks philosopher as full if max_meals is reached.
int	eat(t_philo *philo)
{
	if (sem_wait(philo->sim->forks_sem) == -1
		|| !write_status(philo, GRAB_FORK))
		return (0);
	if (sem_wait(philo->sim->forks_sem) == -1
		|| !write_status(philo, GRAB_FORK))
		return (0);
	if (!set_lsem(&philo->sem, &philo->last_meal_time, get_time(MILLISECOND))
		|| !write_status(philo, EAT))
		return (0);
	philo->eat_count++;
	if (!philo_usleep(philo->sim->stgs.eat_time))
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

// Philosopher thinks. If total philo is odd, wait a bit.
// If not init call (init == 0), print thinking status.
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
	if (!philo_usleep(0.25 * think_time))
		return (0);
	return (1);
}

// Display philosopher action with timestamp.
// Output is protected with semaphore to prevent race.
int	write_status(t_philo *philo, t_status status)
{
	long	time;

	if (philo->full)
		return (1);
	if (sem_wait(philo->sim->output_sem) == -1)
		return (0);
	time = get_time(MILLISECOND)
		- get_lsem(philo->sim->global_sem, &philo->sim->start_time);
	if (time < 0)
		return (sem_post(philo->sim->output_sem), 0);
	if (status == GRAB_FORK)
		print_grab_status(time, philo);
	else if (status == EAT)
		print_eat_status(time, philo, philo->id);
	else if (status == SLEEP)
		print_sleep_status(time, philo->id);
	else if (status == THINK)
		print_think_status(time, philo->id);
	else if (status == DEAD)
		print_death_status(time, philo->id);
	if (sem_post(philo->sim->output_sem) == -1)
		return (0);
	return (1);
}
