/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:33:39 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/10 23:01:14 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int start_simulation(t_sim *sim)
{
	int	i;

	i = -1;
	sim->start_time = get_time(MILLISECOND);
	while (++i < sim->stgs.philo_nb)
	{
		if (pthread_create(&sim->philo[i].thrd_id, NULL, routine, &sim->philo[i]))
			return (0);
	}
	sim->threads_ready = 1;
	return (1);
}

int	simulate_table(t_sim *sim)
{
	if (!start_simulation(sim))
		return (0);
	return (1);
}
