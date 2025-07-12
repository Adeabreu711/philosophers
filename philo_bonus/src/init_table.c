/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:46:06 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/12 15:15:53 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Initialize all simulation semaphores.
static int	init_sim_sems(t_sim *sim)
{
	create_sem(&sim->forks_sem, "/forks_sem", sim->stgs.philo_nb);
	create_sem(&sim->output_sem, "/output_sem", 1);
	create_sem(&sim->start_sem, "/start_sem", 0);
	create_sem(&sim->end_sem, "/end_sem", 0);
	create_sem(&sim->global_sem, "/global_sem", 1);
	if (!sim->start_sem || !sim->end_sem || !sim->global_sem
		|| !sim->forks_sem || !sim->output_sem)
		return (0);
	return (1);
}

// Initialize all philosopher variables.
static int	init_philos(t_sim *sim)
{
	int	i;

	i = -1;
	sim->philo = ft_calloc(sim->stgs.philo_nb, sizeof(t_philo));
	if (!sim->philo)
		return (0);
	while (++i < sim->stgs.philo_nb)
	{
		sim->philo[i].id = i + 1;
		sim->philo[i].eat_count = 0;
		sim->philo[i].last_meal_time = -1;
		sim->philo[i].full = 0;
		sim->philo[i].sim = sim;
		sim->philo[i].pid = 0;
		if (sem_init(&sim->philo[i].sem, 1, 1) == -1)
			return (0);
	}
	return (1);
}

// Initialize all the simulation "sim" struct.
int	init_table(t_sim *sim)
{
	sim->start_time = -1;
	if (!init_sim_sems(sim))
		return (0);
	if (!init_philos(sim))
		return (0);
	if (DEBUG)
		debug_sim(sim);
	return (1);
}
