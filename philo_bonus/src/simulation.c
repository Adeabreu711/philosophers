/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:53:38 by alex              #+#    #+#             */
/*   Updated: 2025/07/12 15:22:50 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Waits for all philosopher processes and the monitor to finish.
// Returns 1 on success, 0 if waitpid fails.
int	wait_philo_end(t_sim *sim)
{
	int		i;
	int		status;

	i = -1;
	waitpid(sim->philo[0].pid, &status, 0);
	while (++i < sim->stgs.philo_nb)
	{
		if (waitpid(sim->philo[i].pid, &status, 0) == -1)
			return (0);
	}
	sem_post(sim->end_sem);
	if (waitpid(sim->monitor_pid, &status, 0) == -1)
		return (0);
	return (1);
}

// Special case for one philosopher. Launch a single process
// Returns 1 on success.
static int	one_philo_case(t_sim *sim)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		philo_alone(&sim->philo[0]);
		exit(0);
	}
	else
		sim->philo[0].pid = pid;
	sem_post(sim->start_sem);
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
	i = -1;
	while (++i < sim->stgs.philo_nb)
		sem_post(sim->start_sem);
	return (1);
}

// Starts the monitor process. Returns 1 on success.
static int	start_monitor(t_sim *sim)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		monitor_routine(sim);
		exit(0);
	}
	sim->monitor_pid = pid;
	sem_post(sim->start_sem);
	return (1);
}

// Starts all routines and waits for completion. Returns 1 on success.
int	simulate_table(t_sim *sim)
{
	sim->start_time = get_time(MILLISECOND);
	if (sim->stgs.philo_nb == 1)
	{
		if (!one_philo_case(sim))
			return (0);
	}
	else if (!simulate_philos(sim))
		return (0);
	if (!start_monitor(sim))
		return (0);
	if (!wait_philo_end(sim))
		return (0);
	return (1);
}
