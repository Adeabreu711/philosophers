/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:31:56 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/02 17:48:33 by alex             ###   ########.fr       */
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

typedef pthread_mutex_t t_mtx;
typedef pthread_t t_thread;

//./philo [philo_nb] [die_time] [eat_time] [sleep_time] ([max_meals])
typedef struct	s_stgs
{
	int		philo_nb;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	int		max_meals;
}	t_stgs;

typedef struct	s_philo
{
	int			id;
	int			eat_count;
	long		last_meal_time;
	void		*l_fork;
	void		*r_fork;
	t_thread	thrd_id;
}	t_philo;

typedef struct	s_fork
{
	t_mtx	mtx;
	int		id;
}	t_fork;

typedef struct	s_sim
{
	t_stgs	stgs;
	t_philo	*philo;
	t_fork	*fork;
	long	start_time;
	int		end_sim;
}	t_sim;


void	*routine(void);

int		parse_settings(t_stgs *stgs, int argc, char *argv[]);
int		init_table(t_sim *sim);

void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
long	ft_atol(const char *nptr);

//DEBUG

void	debug_stgs(t_stgs *stgs);
void	debug_philo(t_sim *sim);

#endif
