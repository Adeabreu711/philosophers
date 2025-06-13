/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:36:04 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/13 23:56:58 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
void	debug_stgs(t_stgs *stgs)
{
	printf("___SETTINGS___\n\n");
	printf("philo_nb : %i\ndie_time : %li\neat_time : %li\nsleep_time : %li\nmax_meals : %i\n\n",
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
		printf ("philo [%i] : \nf_fork [%i] s_fork [%i]\n\n", i + 1, sim->philo[i].f_fork->id, sim->philo[i].s_fork->id);
	}
}

// void	debug_sim(t_sim	*sim)
// {

// }
