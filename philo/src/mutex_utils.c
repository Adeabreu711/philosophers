/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:23:05 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/09 21:45:08 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Add the given int "to_add" to the pointed value "*addr".
// Return 1 on success, 0 on failure.
int	add_imtx(t_mtx *mtx, int *addr, const int to_add)
{
	if (pthread_mutex_lock(mtx))
		return (0);
	*addr += to_add;
	if (pthread_mutex_unlock(mtx))
		return (0);
	return (1);
}

// Set an int protected by a mutex. Return 0 on failure.
int	set_imtx(t_mtx *mtx, int *addr, const int new_nb)
{
	if (pthread_mutex_lock(mtx))
		return (0);
	*addr = new_nb;
	if (pthread_mutex_unlock(mtx))
		return (0);
	return (1);
}

// Set an long int protected by a mutex. Return 0 on failure.
int	set_lmtx(t_mtx *mtx, long *addr, const long new_nb)
{
	if (pthread_mutex_lock(mtx))
		return (0);
	*addr = new_nb;
	if (pthread_mutex_unlock(mtx))
		return (0);
	return (1);
}

// Get an int protected by a mutex. Return 0 on failure.
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

// Get an long int protected by a mutex. Return 0 on failure.
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
