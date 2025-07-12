/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:05:38 by alex              #+#    #+#             */
/*   Updated: 2025/07/12 14:39:38 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Wait with precision using usleep in a more accurate way.
// Usleep is used until a treshold limit, after that CPU is used (busy waiting).
int	philo_usleep(long usec, t_sim *sim)
{
	long	start;
	long	rem;

	start = get_time(MICROSECOND);
	while (1)
	{
		if (get_imtx(&sim->mtx, &sim->end_sim) == 1)
			return (2);
		if (!get_imtx(&sim->mtx, &sim->end_sim))
			return (0);
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
	if (get_imtx(&philo->sim->mtx, &philo->sim->end_sim) == 1)
		return (0);
	if (pthread_mutex_lock(&philo->f_fork->mtx)
		|| !write_status(philo, GRAB_F_FORK))
		return (0);
	if (pthread_mutex_lock(&philo->s_fork->mtx)
		|| !write_status(philo, GRAB_S_FORK))
		return (0);
	if (!set_lmtx(&philo->mtx, &philo->last_meal_time, get_time(MILLISECOND))
		|| !write_status(philo, EAT))
		return (0);
	philo->eat_count++;
	if (!philo_usleep(philo->sim->stgs.eat_time, philo->sim))
		return (0);
	if (philo->sim->stgs.max_meals > 0
		&& philo->eat_count == philo->sim->stgs.max_meals)
	{
		if (!set_imtx(&philo->mtx, &philo->full, 1))
			return (0);
	}
	if (pthread_mutex_unlock(&philo->f_fork->mtx)
		|| pthread_mutex_unlock(&philo->s_fork->mtx))
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
	if (pthread_mutex_lock(&philo->sim->output_mtx))
		return (0);
	end_sim = get_imtx(&philo->sim->mtx, &philo->sim->end_sim);
	time = get_time(MILLISECOND)
		- get_lmtx(&philo->sim->mtx, &philo->sim->start_time);
	if (!end_sim || time < 0)
		return (0);
	if ((status == GRAB_F_FORK || status == GRAB_S_FORK) && end_sim == -1)
		print_grab_status(time, philo, status);
	else if (status == EAT && end_sim == -1)
		print_eat_status(philo->sim, time, philo->id);
	else if (status == SLEEP && end_sim == -1)
		print_sleep_status(time, philo->id);
	else if (status == THINK && end_sim == -1)
		print_think_status(time, philo->id);
	else if (status == DEAD)
		print_death_status(time, philo->id);
	if (pthread_mutex_unlock(&philo->sim->output_mtx))
		return (0);
	return (1);
}
