/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:03:45 by alex              #+#    #+#             */
/*   Updated: 2025/06/18 18:24:12 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	synchronize_threads(t_sim *sim, int value)
{
	if (!get_imtx(&sim->mtx, &sim->threads_ready))
		return (0);
	while (get_imtx(&sim->mtx, &sim->threads_ready) < value)
		continue;
	return (1);
}

int	check_death(t_philo *philo)
{
	long	time;
	long	lst_meal_t;

	if (get_imtx(&philo->mtx, &philo->full) == 1)
		return (0);
	lst_meal_t = get_lmtx(&philo->mtx, &philo->last_meal_time);
	time = get_time(MILLISECOND);
	if (!time || !lst_meal_t)
		return (-1);
	//printf("philo %i : time before death %li / %li\n", philo->id, time - lst_meal_t, philo->sim->stgs.die_time);
	if ((time - lst_meal_t) > philo->sim->stgs.die_time / 1e3)
		return (1);
	return (0);
}
