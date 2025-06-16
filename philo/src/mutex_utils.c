/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:23:05 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/14 17:40:17 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// add the given int "to_add" to the pointed value "*addr".
// return 1 on success, 0 on failure
int	add_imtx(t_mtx *mtx, int *addr, const int to_add)
{
	if (pthread_mutex_lock(mtx))
		return (0);
	*addr += to_add;
	if (pthread_mutex_unlock(mtx))
		return (0);
	return (1);
}

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
