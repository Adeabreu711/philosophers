/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:36:04 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/07 11:03:33 by alde-abr         ###   ########.fr       */
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
		printf ("philo [%i] : \nl_fork [%p]\nr_fork [%p]\n\n", i, sim->philo[i].f_fork, sim->philo[i].s_fork);
	}
}

// void	debug_sim(t_sim	*sim)
// {

// }
