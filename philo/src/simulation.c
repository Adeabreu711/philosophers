/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:33:39 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/20 15:30:18 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Init the philo_alone thread and the monitor thread.
// Set start time and threads_ready.
static int	one_philo_case(t_sim *sim)
{
	if (pthread_create(&sim->philo[0].thrd_id, NULL,
			philo_alone, &sim->philo[0]))
		return (0);
	if (pthread_create(&sim->monitor, NULL, monitor_routine, sim))
		return (0);
	wait_start(sim->start_time);
	return (1);
}

// Join all threads, waiting for them to finish.
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

// Init all the philos threads and the monitor thread.
// Set start time and threads_ready.
static int	simulate_philos(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->stgs.philo_nb)
	{
		if (pthread_create(&sim->philo[i].thrd_id, NULL,
				philo_routine, &sim->philo[i]))
			return (0);
	}
	if (pthread_create(&sim->monitor, NULL, monitor_routine, sim))
		return (0);
	return (1);
}

// Simulate the diner until an error occur, a philo die
// or a all philos are full.
int	simulate_table(t_sim *sim)
{
	if (sim->stgs.philo_nb == 1)
	{
		if (!one_philo_case(sim))
			return (0);
	}
	else if (!simulate_philos(sim))
		return (0);
	if (!check_philos_full(sim))
		return (0);
	if (!set_imtx(&sim->mtx, &sim->end_sim, 1))
		return (0);
	if (pthread_join(sim->monitor, NULL))
		return (0);
	return (1);
}
