/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:44:58 by alex              #+#    #+#             */
/*   Updated: 2025/06/13 23:52:12 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	if (!synchronize_threads(philo->sim))
		return (0);
	//set last meal;

	//printf("philo [%i] : f_fork [%i], s_fork [%i]\n", philo->id, philo->f_fork->id, philo->s_fork->id);
	while (get_imtx(&philo->sim->mtx, &philo->sim->end_sim) == -1)
	{
		if (philo->full == 1)
			break;
		eat(philo);
		if (!write_status(philo, SLEEP)
			|| !philo_usleep(philo->sim->stgs.sleep_time, philo->sim))
			return (NULL);
		think(philo);
	}
	if (!get_imtx(&philo->sim->mtx, &philo->sim->end_sim))
		return (NULL);
	return (NULL);
}
