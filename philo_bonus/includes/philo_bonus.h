/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:31:56 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/08 16:33:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include "time.h"
# include <limits.h>
# include <semaphore.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

typedef pthread_mutex_t	t_mtx;
typedef pthread_t		t_thread;
typedef struct s_sim	t_sim;

typedef enum e_status
{
	GRAB_F_FORK,
	GRAB_S_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_status;

//./philo [philo_nb] [die_time] [eat_time] [sleep_time] ([max_meals])
typedef struct s_stgs
{
	int		philo_nb;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	int		max_meals;
}	t_stgs;

typedef struct s_philo
{
	int			id;
	int			eat_count;
	long		last_meal_time;
	int			full;
	pid_t		pid;
	sem_t		sem;
	t_sim		*sim;
}	t_philo;

struct	s_sim
{
	t_stgs		stgs;
	t_philo		*philo;
	sem_t		*forks_sem;
	sem_t		*output_sem;
	sem_t		*start_sem;
	pid_t		monitor_pid;
	long		start_time;
	sem_t		*end_sem;
	sem_t		*global_sem;
};

int		simulate_table(t_sim *sim);

//ROUTINES

void	*philo_routine(void *data);
void	*philo_alone(void *data);
void	*monitor_routine(void *data);

//ROUTINE UTILS

int		adapt_fairness(t_philo *philo);
int		synchronize_threads(t_sim *sim, int value);
int		check_death(t_philo *philo);
int		kill_all_process(t_sim *sim);

//PARSING

int		parse_settings(t_stgs *stgs, int argc, char *argv[]);
int		init_table(t_sim *sim);

//PHILO UTILS

int		philo_usleep(long usec, t_sim *sim);
int		write_status(t_philo *philo, t_status status);
int		eat(t_philo *philo);
int		think(t_philo *philo, int init);

//GET/SET

void	destroy_sem(sem_t *sem, const char *path);
long	get_lsem(sem_t *sem, long *addr);
int		get_isem(sem_t *sem, int *addr);
int		set_lsem(sem_t *sem, long *addr, const long new_nb);
int		set_isem(sem_t *sem, int *addr, const int new_nb);

//OTHERS

void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
long	ft_atol(const char *nptr);

//DEBUG

void	debug_stgs(t_stgs *stgs);
void	debug_philo(t_sim *sim);
int		simulate_test(t_sim *sim);

#endif
