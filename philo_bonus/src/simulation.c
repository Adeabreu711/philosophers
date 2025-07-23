/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:53:38 by alex              #+#    #+#             */
/*   Updated: 2025/07/23 15:45:02 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Waits for the monitor to finish.
// Returns 1 on success, 0 if waitpid fails.
int	wait_philo_end(t_sim *sim)
{
	int	i;

	i = -1;
	while (++ i < sim->stgs.philo_nb)
	{
		if (sem_wait(sim->end_sem) == -1)
			return (0);
	}
	kill_all_child(sim);
	return (1);
}

// Fork one process per philosopher and start their routine.
// Returns 1 on success.
static int	simulate_philos(t_sim *sim)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < sim->stgs.philo_nb)
		sem_post(sim->start_sem);
	i = -1;
	while (++i < sim->stgs.philo_nb)
	{
		pid = fork();
		if (pid < 0)
			return (0);
		else if (pid == 0)
		{
			philo_routine(&sim->philo[i]);
			exit(0);
		}
		else
			sim->philo[i].pid = pid;
	}
	return (1);
}

// Starts all routines and waits for completion. Returns 1 on success.
int	simulate_table(t_sim *sim)
{
	sim->start_time = get_time(MILLISECOND);
	if (!simulate_philos(sim))
		return (0);
	if (!wait_philo_end(sim))
		return (0);
	return (1);
}
