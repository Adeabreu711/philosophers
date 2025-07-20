/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:57:28 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 15:30:33 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#define ORANGE "\033[38;5;214m"
#define YELLOW "\033[38;5;222m"
#define RED    "\033[38;5;208m"
#define BLUE "\033[36m"
#define RESET  "\033[0m"
#define WHITE  "\033[1;97m"

// print "eating" status, more if debug active.
int	print_eat_status(t_sim *sim, long time, int id)
{
	if (!DEBUG)
		return (printf("%li %i is eating\n", time, id), 1);
	printf("%s[%6li]%s Philo %i is eating %s[🍝 %i]%s\n\n",
		BLUE, time, WHITE, id, BLUE, sim->philo[id - 1].eat_count + 1, RESET);
	return (1);
}

// print "sleeping" status, more if debug active.
int	print_sleep_status(long time, int id)
{
	if (!DEBUG)
		return (printf("%li %i is sleeping\n", time, id), 1);
	printf("%s[%6li]%s Philo %i is sleeping 💤\n",
		BLUE, time, RESET, id);
	return (1);
}

// print "thinking" status, more if debug active.
int	print_think_status(long time, int id)
{
	if (!DEBUG)
		return (printf("%li %i is thinking\n", time, id), 1);
	printf("%s[%6li]%s Philo %i is thinking 💭\n",
		BLUE, time, RESET, id);
	return (1);
}

// print "taken a fork" status, more if debug active.
int	print_grab_status(long time, t_philo *philo, t_status status)
{
	if (!DEBUG)
		return (printf("%li %i has taken a fork\n", time, philo->id), 1);
	if (status == GRAB_F_FORK)
		printf("%s[%6li]%s Philo %i has taken his first fork %s[🍴 %i]%s\n",
			BLUE, time, RESET, philo->id, YELLOW, philo->f_fork->id, RESET);
	else
		printf("%s[%6li]%s Philo %i has taken his second fork %s[🍴 %i]%s\n",
			BLUE, time, RESET, philo->id, ORANGE, philo->s_fork->id, RESET);
	return (1);
}

// print "died" status, more if debug active.
int	print_death_status(long time, int id)
{
	if (!DEBUG)
		return (printf("%li %i died\n", time, id), 1);
	printf("%s[%6li] Philo %i died 🪦%s\n",
		RED, time, id, RESET);
	return (1);
}
