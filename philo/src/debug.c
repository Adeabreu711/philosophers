/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:43:46 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 15:29:32 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	debug_param(t_stgs *stgs)
{
	printf("\n\033[1;97m____PARAMETERS______\033[0m\n\n");
	printf("philo_nb   : %i\n", stgs->philo_nb);
	printf("die_time   : %lims (%fsec)\n",
		stgs->die_time / (long)1e3, (double)stgs->die_time / 1e6);
	printf("eat_time   : %lims (%fsec)\n",
		stgs->eat_time / (long)1e3, (double)stgs->eat_time / 1e6);
	printf("sleep_time : %lims (%fsec)\n",
		stgs->sleep_time / (long)1e3, (double)stgs->sleep_time / 1e6);
	printf("max_meals  : %i\n\n", stgs->max_meals);
}

static void	debug_forks(t_sim *sim)
{
	int	i;

	i = -1;
	printf("\033[1;97m____FORKS__________\033[0m\n\n");
	while (++i < sim->stgs.philo_nb)
	{
		printf("Philo [%i]\n first fork -> %i\n  second fork -> %i\n\n",
			i + 1, sim->philo[i].f_fork->id, sim->philo[i].s_fork->id);
	}
}

void	debug_sim(t_sim *sim)
{
	debug_param(&sim->stgs);
	debug_forks(sim);
	printf("\033[1;97m____SIMULATION_____\033[0m\n\n");
}
