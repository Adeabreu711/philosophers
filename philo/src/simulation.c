/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:33:39 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/13 23:09:57 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
static int check_philos_full(t_sim * sim)
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

static int start_simulation(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->stgs.philo_nb)
	{
		if (pthread_create(&sim->philo[i].thrd_id, NULL, routine, &sim->philo[i]))
			return (0);
	}
	sim->start_time = get_time(MILLISECOND);
	if (!set_imtx(&sim->mtx, &sim->threads_ready, 1))
		return (0);
	return (1);
}

int	simulate_table(t_sim *sim)
{
	if (!start_simulation(sim))
		return (0);
	if (!check_philos_full(sim))
		return (0);
	return (1);
}
