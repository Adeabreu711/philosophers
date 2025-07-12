/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:34:42 by alex              #+#    #+#             */
/*   Updated: 2025/07/09 15:48:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// Close the given semaphore and unlink its named path.
void	destroy_sem(sem_t *sem, const char *path)
{
	if (sem)
		sem_close(sem);
	sem_unlink(path);
}

// Create and open a named semaphore. Return 1 on success, 0 on failure.
int	create_sem(sem_t **sem, const char *path, int value)
{
	sem_unlink(path);
	*sem = sem_open(path, O_CREAT | O_EXCL, 0644, value);
	if (*sem == SEM_FAILED)
		return (0);
	return (1);
}
