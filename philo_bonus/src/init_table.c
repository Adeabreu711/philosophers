/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:46:06 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/08 16:11:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	init_forks_sem(t_sim *sim)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_output");
	sim->forks_sem = sem_open("/sem_forks", O_CREAT, 0644, sim->stgs.philo_nb);
	if (sim->forks_sem == SEM_FAILED)
		return (0);
	sim->output_sem = sem_open("/sem_output", O_CREAT, 0644, 1);
	if (sim->output_sem == SEM_FAILED)
		return (0);
	return (1);
}

// Initialize all philos variables.
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
	sem_unlink("/start_sem");
	sem_unlink("/end_sem");
	sem_unlink("/global_sem");
	sim->start_sem = sem_open("/start_sem", O_CREAT | O_EXCL, 0644, 0);
	if (sim->start_sem == SEM_FAILED)
		return (0);
	sim->global_sem= sem_open("/global_sem", O_CREAT | O_EXCL, 0644, 1);
	if (sim->global_sem == SEM_FAILED)
		return (0);
	sim->end_sem = sem_open("/end_sem", O_CREAT | O_EXCL, 0644, 0);
	if (sim->end_sem == SEM_FAILED)
		return (0);
	sim->start_time = -1;
	if (!init_forks_sem(sim))
		return (0);
	if (!init_philos(sim))
		return (0);
	return (1);
}
