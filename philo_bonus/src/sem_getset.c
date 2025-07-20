/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_getset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:23:05 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/20 15:32:09 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Set an int protected by a semaphore. Return 0 on failure.
int	set_isem(sem_t *sem, int *addr, const int new_nb)
{
	if (sem_wait(sem) == -1)
		return (0);
	*addr = new_nb;
	if (sem_post(sem) == -1)
		return (0);
	return (1);
}

// Set a long protected by a semaphore. Return 0 on failure.
int	set_lsem(sem_t *sem, long *addr, const long new_nb)
{
	if (sem_wait(sem) == -1)
		return (0);
	*addr = new_nb;
	if (sem_post(sem) == -1)
		return (0);
	return (1);
}

// Get an int protected by a semaphore. Return 0 on failure.
int	get_isem(sem_t *sem, int *addr)
{
	int	nb;

	if (sem_wait(sem) == -1)
		return (0);
	nb = *addr;
	if (sem_post(sem) == -1)
		return (0);
	return (nb);
}

// Get a long protected by a semaphore. Return 0 on failure.
long	get_lsem(sem_t *sem, long *addr)
{
	long	nb;

	if (sem_wait(sem) == -1)
		return (0);
	nb = *addr;
	if (sem_post(sem) == -1)
		return (0);
	return (nb);
}
