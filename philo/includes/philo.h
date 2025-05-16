/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:31:56 by alde-abr          #+#    #+#             */
/*   Updated: 2025/05/16 22:05:41 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>	//usleep
# include <pthread.h>	//MUTEX : init; destroy; lock; unlock;
						//THREADS : create; join; detach;
#include <sys/time.h>	//gettimeofday
#include <limits.h>

//./philo [philo_nb] [die_time] [eat_time] [die_time] [sleep_time] ([max_meals])
typedef struct	s_stgs
{
	int		philo_nb;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		max_meals;
}	t_stgs;

typedef struct	s_philo
{
	int		id;
	void	*l_fork;
	void	*r_fork;
}	t_philo;

typedef struct	s_fork
{
	int		id;
}	t_fork;

typedef struct	s_sim
{
	t_stgs	stgs;
	t_philo	*philo;
	t_fork	*fork;
	long	start_time;
}	t_sim;


int		parse_simulation(t_sim *sim, int argc, char *argv[]);

void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_atoi_lmt(const char *nptr);

//DEBUG

void	debug_stgs(t_stgs *stgs);

#endif
