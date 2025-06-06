/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:46:06 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/06 17:07:18 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	set_forks(t_fork *fork, int philo_nb)
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

static int	set_philos(t_philo *philo, t_fork *fork, int philo_nb)
{
	int	i;

	i = -1;
	philo = ft_calloc(philo_nb + 1, sizeof(t_philo));
	if (!philo)
		return (0);
	while (++i < philo_nb)
	{
		philo[i].id = i;
		philo[i].eat_count = 0;
		philo[i].last_meal_time = -1;
		philo[i].l_fork = &fork[i];
		philo[i].r_fork = &fork[(philo_nb + i - 1) % philo_nb];
		// if (pthread_create(philo[i].thrd_id, NULL, &routine, NULL))
		// 	return (0);
		printf ("Philo [%i] : l_fork[%i], r_fork[%i]\n", i, i, (philo_nb + i - 1) % philo_nb);
	}
	return (1);
}

int	init_table(t_sim *sim)
{
	sim->end_sim = 0;

	if (!set_forks(sim->fork, sim->stgs.philo_nb))
		return (0);
	if (!set_philos(sim->philo, sim->fork, sim->stgs.philo_nb))
		return (0);
	// debug_philo(sim);
	return (1);
}
