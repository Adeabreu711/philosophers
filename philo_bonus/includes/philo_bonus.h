/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:31:56 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/20 15:31:20 by alde-abr         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_sim	t_sim;
typedef pthread_t		t_thread;

typedef enum e_status
{
	GRAB_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_status;

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
	t_thread	monitor;
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
int		send_death_report(t_philo *philo);
int		kill_all_child(t_sim *sim);

//PARSING

int		parse_settings(t_stgs *stgs, int argc, char *argv[]);
int		init_table(t_sim *sim);

//PHILO UTILS

int		philo_usleep(long usec);
int		write_status(t_philo *philo, t_status status);
int		eat(t_philo *philo);
int		think(t_philo *philo, int init);

//SEM_UTILS

void	destroy_sem(sem_t *sem, const char *path);
int		create_sem(sem_t **sem, const char *path, int value);

//GET/SET

long	get_lsem(sem_t *sem, long *addr);
int		get_isem(sem_t *sem, int *addr);
int		set_lsem(sem_t *sem, long *addr, const long new_nb);
int		set_isem(sem_t *sem, int *addr, const int new_nb);

//STATUS

int		print_eat_status(long time, t_philo *philo, int id);
int		print_sleep_status(long time, int id);
int		print_think_status(long time, int id);
int		print_death_status(long time, int id);
int		print_grab_status(long time, t_philo *philo);

//OTHERS

void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
long	ft_atol(const char *nptr);

//DEBUG

void	debug_sim(t_sim *sim);

#endif
