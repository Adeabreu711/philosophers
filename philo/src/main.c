/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:40:31 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/09 21:57:10 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Free all the allocated memory in the simulation struct.
int	free_sim(t_sim *sim)
{
	if (!sim)
		return (0);
	if (sim->philo)
		free(sim->philo);
	if (sim->fork)
		free(sim->fork);
	free(sim);
	return (1);
}

// Philosophers mandatory part.
int	main(int argc, char *argv[])
{
	t_sim	*sim;

	sim = ft_calloc(1, sizeof(t_sim));
	if (!sim)
		return (0);
	if (!parse_settings(&sim->stgs, argc, argv) || !init_table(sim))
		return (free_sim(sim), 0);
	if (!simulate_table(sim))
		return (free_sim(sim), 0);
	return (free_sim(sim), 1);
}
