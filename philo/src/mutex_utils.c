/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:23:05 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/13 22:54:06 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// return 1 on success, 0 on failure
int	set_imtx(t_mtx *mtx, int *addr, const int new_nb)
{
	if (pthread_mutex_lock(mtx))
		return (0);
	*addr = new_nb;
	if (pthread_mutex_unlock(mtx))
		return (0);
	return (1);
}

// return 1 on success, 0 on failure
int	set_lmtx(t_mtx *mtx, long *addr, const long new_nb)
{
	if (pthread_mutex_lock(mtx))
		return (0);
	*addr = new_nb;
	if (pthread_mutex_unlock(mtx))
		return (0);
	return (1);
}

// return addr value on success, 0 on failure
int	get_imtx(t_mtx *mtx, int *addr)
{
	int	nb;

	if (pthread_mutex_lock(mtx))
		return (0);
	nb = *addr;
	if (pthread_mutex_unlock(mtx))
		return (0);
	return (nb);
}

// return addr value on success, 0 on failure
long	get_lmtx(t_mtx *mtx, long *addr)
{
	long	nb;

	if (pthread_mutex_lock(mtx))
		return (0);
	nb = *addr;
	if (pthread_mutex_unlock(mtx))
		return (0);
	return (nb);
}
