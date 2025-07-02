/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:33:39 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/02 16:05:59 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	one_philo_case(t_sim *sim)
{
	if (pthread_create(&sim->philo[0].thrd_id, NULL,
			philo_alone, &sim->philo[0]))
		return (0);
	sim->start_time = get_time(MILLISECOND);
	if (pthread_create(&sim->monitor, NULL, monitor_routine, sim))
		return (0);
	if (!set_imtx(&sim->mtx, &sim->threads_ready, 1))
		return (0);
	return (1);
}

static int	check_philos_full(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->stgs.philo_nb)
	{
		if (pthread_join(sim->philo[i].thrd_id, NULL))
			return (0);
	}
	return (1);
}

static int	start_simulation(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->stgs.philo_nb)
	{
		if (pthread_create(&sim->philo[i].thrd_id, NULL,
				philo_routine, &sim->philo[i]))
			return (0);
	}
	sim->start_time = get_time(MILLISECOND);
	if (pthread_create(&sim->monitor, NULL, monitor_routine, sim))
		return (0);
	if (!set_imtx(&sim->mtx, &sim->threads_ready, 1))
		return (0);
	return (1);
}

int	simulate_table(t_sim *sim)
{
	if (sim->stgs.philo_nb == 1)
	{
		if (!one_philo_case(sim))
			return (0);
	}
	else if (!start_simulation(sim))
		return (0);
	if (!check_philos_full(sim))
		return (0);
	if (!set_imtx(&sim->mtx, &sim->end_sim, 1))
		return (0);
	if (pthread_join(sim->monitor, NULL))
		return (0);
	return (1);
}
