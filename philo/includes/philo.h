/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:31:56 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/13 23:26:53 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
#include "time.h"
#include <limits.h>

typedef pthread_mutex_t t_mtx;
typedef pthread_t t_thread;
typedef struct s_sim t_sim;

typedef enum e_status
{
	GRAB_F_FORK,
	GRAB_S_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
} t_status;

//./philo [philo_nb] [die_time] [eat_time] [sleep_time] ([max_meals])
typedef struct	s_stgs
{
	int		philo_nb;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	int		max_meals;
}	t_stgs;

typedef struct	s_fork
{
	t_mtx	mtx;
	int		id;
}	t_fork;

typedef struct	s_philo
{
	int			id;
	int			eat_count;
	long		last_meal_time;
	t_fork		*f_fork;
	t_fork		*s_fork;
	int			full;
	t_thread	thrd_id;
	t_sim		*sim;
	t_mtx		mtx;
}	t_philo;

struct	s_sim
{
	t_stgs	stgs;
	t_philo	*philo;
	t_fork	*fork;
	t_mtx	mtx;
	t_mtx	output_mtx;
	long	start_time;
	int		threads_ready;
	int		end_sim;
};

int		simulate_table(t_sim *sim);
void	*routine(void *);

int		parse_settings(t_stgs *stgs, int argc, char *argv[]);
int		init_table(t_sim *sim);

//PHILO UTILS

int	synchronize_threads(t_sim *sim);
int	philo_usleep(long usec, t_sim *sim);
int	write_status(t_philo *philo, t_status status);
int	eat(t_philo *philo);
int	think(t_philo *philo);

//GET/SET
long	get_lmtx(t_mtx *mtx, long *addr);
int		get_imtx(t_mtx *mtx, int *addr);
int		set_lmtx(t_mtx *mtx, long *addr, const long new_nb);
int		set_imtx(t_mtx *mtx, int *addr, const int new_nb);

//OTHERS

void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
long	ft_atol(const char *nptr);

//DEBUG

void	debug_stgs(t_stgs *stgs);
void	debug_philo(t_sim *sim);

#endif
