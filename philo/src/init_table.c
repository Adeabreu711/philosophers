/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:46:06 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/07 11:03:51 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_forks_addr(t_philo *philo, t_fork *forks, int i, int philo_nb)
{
	if ((i + 1) % 2 == 0)
	{
		philo[i].f_fork = &forks[i];
		philo[i].s_fork = &forks[(philo_nb + i - 1) % philo_nb];
		//printf("Philo [%i] : l_fork[%i], r_fork[%i]\n", i, (philo_nb + i - 1) % philo_nb, i);
		return ;
	}
	philo[i].f_fork = &forks[(philo_nb + i - 1) % philo_nb];
	philo[i].s_fork = &forks[i];
	//printf("Philo [%i] : l_fork[%i], r_fork[%i]\n", i, i, (philo_nb + i - 1) % philo_nb);
}

static int	init_forks(t_fork *fork, int philo_nb)
{
	int	i;

	i = -1;
	fork = ft_calloc(philo_nb + 1, sizeof(t_fork));
	if (!fork)
		return (0);
	while (++i < philo_nb)
	{
		fork[i].id = i;
		if (pthread_mutex_init(&fork[i].mtx, NULL))
			return (0);
	}
	return (1);
}

static int	init_philos(t_philo *philo, t_fork *fork, int philo_nb)
{
	int	i;

	i = -1;
	philo = ft_calloc(philo_nb + 1, sizeof(t_philo));
	if (!philo)
		return (0);
	while (++i < philo_nb)
	{
		philo[i].id = i + 1;
		philo[i].eat_count = 0;
		philo[i].last_meal_time = -1;
		philo[i].full = 0;
		set_forks_addr(philo, fork, i, philo_nb);
	}
	return (1);
}

int	init_table(t_sim *sim)
{
	sim->end_sim = 0;
	if (!init_forks(sim->fork, sim->stgs.philo_nb))
		return (0);
	if (!init_philos(sim->philo, sim->fork, sim->stgs.philo_nb))
		return (0);
	// debug_philo(sim);
	return (1);
}
