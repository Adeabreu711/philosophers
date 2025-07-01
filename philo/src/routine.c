/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:44:58 by alex              #+#    #+#             */
/*   Updated: 2025/07/01 14:13:35 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!synchronize_threads(philo->sim, 1))
		return (NULL);
	if (!add_imtx(&philo->sim->mtx, &philo->sim->threads_ready, 1))
		return (NULL);
	if (!set_lmtx(&philo->mtx, &philo->last_meal_time, get_time(MILLISECOND)))
		return (NULL);
	if (!write_status(philo, GRAB_F_FORK))
		return (NULL);
	while (get_imtx(&philo->sim->mtx, &philo->sim->end_sim) == -1)
		usleep(200);
	return (NULL);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!synchronize_threads(philo->sim, 1))
		return (NULL);
	if (!add_imtx(&philo->sim->mtx, &philo->sim->threads_ready, 1))
		return (NULL);
	if (!set_lmtx(&philo->mtx, &philo->last_meal_time, get_time(MILLISECOND)))
		return (NULL);
	while (get_imtx(&philo->sim->mtx, &philo->sim->end_sim) == -1)
	{
		if (philo->full == 1)
			break;
		eat(philo);
		if (!write_status(philo, SLEEP)
			|| !philo_usleep(philo->sim->stgs.sleep_time, philo->sim))
			return (NULL);
		think(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *data)
{
	int		i;
	t_sim	*sim;

	i = -1;
	sim = data;
	if (!synchronize_threads(sim, sim->stgs.philo_nb + 1))
		return (NULL);
	// printf("start time : %li\n", sim->start_time);
	while (get_imtx(&sim->mtx, &sim->end_sim) == -1)
	{
		while (++i < sim->stgs.philo_nb)
		{
			if (check_death(&sim->philo[i]) == 1)
			{
				if (!set_imtx(&sim->mtx, &sim->end_sim, 1))
					return (NULL);
				write_status(&sim->philo[i], DEAD);
				break;
			}
		}
		i = -1;
	}
	return (NULL);
}
