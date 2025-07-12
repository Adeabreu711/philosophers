/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:57:28 by alex              #+#    #+#             */
/*   Updated: 2025/07/12 15:09:18 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ORANGE "\033[38;5;214m"
#define YELLOW "\033[38;5;222m"
#define RED    "\033[38;5;208m"
#define L_BLUE "\033[36m"
#define RESET  "\033[0m"
#define WHITE  "\033[1;97m"

#include "../includes/philo.h"

int	print_eat_status(t_sim *sim, long time, int id)
{
	if (!DEBUG)
		return (printf("%li %i is eating\n", time, id), 1);
	printf("%s[%6li]%s Philo %i is eating %s[🍝 %i]%s\n\n",
		L_BLUE, time, WHITE, id, L_BLUE, sim->philo[id].eat_count + 1, RESET);
	return (1);
}

int	print_sleep_status(long time, int id)
{
	if (!DEBUG)
		return (printf("%li %i is sleeping\n", time, id), 1);
	printf("%s[%6li]%s Philo %i is sleeping 💤\n",
		L_BLUE, time, RESET, id);
	return (1);
}

int	print_think_status(long time, int id)
{
	if (!DEBUG)
		return (printf("%li %i is thinking\n", time, id), 1);
	printf("%s[%6li]%s Philo %i is thinking 💭\n",
		L_BLUE, time, RESET, id);
	return (1);
}

int	print_grab_status(long time, t_philo *philo, t_status status)
{
	if (!DEBUG)
		return (printf("%li %i has taken a fork\n", time, philo->id), 1);
	if (status == GRAB_F_FORK)
		printf("%s[%6li]%s Philo %i has taken his first fork %s[🍴 %i]%s\n",
			L_BLUE, time, RESET, philo->id, YELLOW, philo->f_fork->id, RESET);
	else
		printf("%s[%6li]%s Philo %i has taken his second fork %s[🍴 %i]%s\n",
			L_BLUE, time, RESET, philo->id, ORANGE, philo->s_fork->id, RESET);
	return (1);
}

int	print_death_status(long time, int id)
{
	if (!DEBUG)
		return (printf("%li %i died\n", time, id), 1);
	printf("%s[%6li] Philo %i died 🪦%s\n",
		RED, time, id, RESET);
	return (1);
}
