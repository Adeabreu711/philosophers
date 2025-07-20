/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:43:46 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 15:31:27 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

void	debug_sim(t_sim *sim)
{
	debug_param(&sim->stgs);
	printf("\033[1;97m____SIMULATION_____\033[0m\n\n");
}
