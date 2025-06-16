/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:40:31 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/16 19:31:02 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	printf ("threads ready : %i\n", sim->threads_ready);
	printf ("end sim : %i\n", sim->end_sim);
	return (free_sim(sim), 1);
}
