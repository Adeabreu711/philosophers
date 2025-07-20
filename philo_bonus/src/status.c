/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:57:28 by alex              #+#    #+#             */
/*   Updated: 2025/07/20 15:10:12 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

#define ORANGE "\033[38;5;214m"
#define YELLOW "\033[38;5;222m"
#define RED    "\033[38;5;208m"
#define BLUE "\033[36m"
#define RESET  "\033[0m"
#define WHITE  "\033[1;97m"

int	print_eat_status(long time, t_philo *philo, int id)
{
	if (!DEBUG)
		return (printf("%li %i is eating\n", time, id), 1);
	printf("%s[%6li]%s Philo %i is eating %s[🍝 %i]%s\n\n",
		BLUE, time, WHITE, id, BLUE, philo->eat_count + 1, RESET);
	return (1);
}

int	print_sleep_status(long time, int id)
{
	if (!DEBUG)
		return (printf("%li %i is sleeping\n", time, id), 1);
	printf("%s[%6li]%s Philo %i is sleeping 💤\n",
		BLUE, time, RESET, id);
	return (1);
}

int	print_think_status(long time, int id)
{
	if (!DEBUG)
		return (printf("%li %i is thinking\n", time, id), 1);
	printf("%s[%6li]%s Philo %i is thinking 💭\n",
		BLUE, time, RESET, id);
	return (1);
}

int	print_grab_status(long time, t_philo *philo)
{
	if (!DEBUG)
		return (printf("%li %i has taken a fork\n", time, philo->id), 1);
	printf("%s[%6li]%s Philo %i has taken a fork\n",
		BLUE, time, RESET, philo->id);
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
