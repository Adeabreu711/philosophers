/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:23:05 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/08 16:32:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Close the given semaphore and unlike his path.
void	destroy_sem(sem_t *sem, const char *path)
{
	if (sem)
		sem_close(sem);
	sem_unlink(path);
}

// Return 1 on success, 0 on failure.
int	set_isem(sem_t *sem, int *addr, const int new_nb)
{
	if (sem_wait(sem) == -1)
		return (0);
	*addr = new_nb;
	if (sem_post(sem) == -1)
		return (0);
	return (1);
}

// Return 1 on success, 0 on failure.
int	set_lsem(sem_t *sem, long *addr, const long new_nb)
{
	if (sem_wait(sem) == -1)
		return (0);
	*addr = new_nb;
	if (sem_post(sem) == -1)
		return (0);
	return (1);
}

// Return addr value on success, 0 on failure.
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

// Return addr value on success, 0 on failure.
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
