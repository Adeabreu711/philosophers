/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:46:06 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/13 23:47:13 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_forks_addr(t_philo *philo, t_fork *forks, int i, int philo_nb)
{
	if ((i + 1) % 2 == 0)
	{
		philo[i].f_fork = &forks[i];
		philo[i].s_fork = &forks[(philo_nb + i - 1) % philo_nb];
		printf("Philo [%i] : l_fork[%i], r_fork[%i]\n", i, (philo_nb + i - 1) % philo_nb, i);
		return ;
	}
	philo[i].f_fork = &forks[(philo_nb + i - 1) % philo_nb];
	philo[i].s_fork = &forks[i];
	printf("Philo [%i] : l_fork[%i], r_fork[%i]\n", i, i, (philo_nb + i - 1) % philo_nb);
}

static int	init_forks(t_sim *sim)
{
	int	i;

	i = -1;
	sim->fork = ft_calloc(sim->stgs.philo_nb, sizeof(t_fork));
	if (!sim->fork)
		return (0);
	while (++i < sim->stgs.philo_nb)
	{
		sim->fork[i].id = i;
		if (pthread_mutex_init(&sim->fork[i].mtx, NULL))
			return (0);
	}
	return (1);
}

static int	init_philos(t_sim *sim)
{
	int	i;

	i = -1;
	sim->philo = ft_calloc(sim->stgs.philo_nb, sizeof(t_philo));
	if (!sim->philo)
		return (0);
	while (++i < sim->stgs.philo_nb)
	{
		if (pthread_mutex_init(&sim->philo[i].mtx, NULL))
			return (0);
		sim->philo[i].id = i + 1;
		sim->philo[i].eat_count = 0;
		sim->philo[i].last_meal_time = -1;
		sim->philo[i].full = 0;
		sim->philo[i].sim = sim;
		set_forks_addr(sim->philo, sim->fork, i, sim->stgs.philo_nb);
	}
	return (1);
}

int	init_table(t_sim *sim)
{
	sim->end_sim = -1;
	sim->start_time = -1;
	sim->threads_ready = -1;
	if (pthread_mutex_init(&sim->mtx, NULL))
		return (0);
	if (!init_forks(sim))
		return (0);
	if (!init_philos(sim))
		return (0);
	debug_philo(sim);
	return (1);
}
