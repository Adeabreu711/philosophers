/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:36:04 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/02 17:51:50 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
void	debug_stgs(t_stgs *stgs)
{
	printf("___SETTINGS___\n\n");
	printf("philo_nb : %i\ndie_time : %li\neat_time : %li\nsleep_time : %li\nmax_meals : %i\n",
		stgs->philo_nb,
		stgs->die_time,
		stgs->eat_time,
		stgs->sleep_time,
		stgs->max_meals);
}

void	debug_philo(t_sim *sim)
{
	int	i;

	i = -1;
	printf("___PHILOS___\n\n");
	while (++i < sim->stgs.philo_nb)
	{
		printf ("philo [%i] : \nl_fork [%p]\nr_fork [%p]\n\n", i, sim->philo[i].l_fork, sim->philo[i].r_fork);
	}
}

// void	debug_sim(t_sim	*sim)
// {

// }
