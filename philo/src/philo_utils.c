/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:05:38 by alex              #+#    #+#             */
/*   Updated: 2025/06/10 23:01:14 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	synchronize_threads(t_sim *sim)
{
	while (!get_imtx(&sim->mtx, sim->threads_ready))
		continue ;
	return (1);
}
