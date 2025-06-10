/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:46:10 by alde-abr          #+#    #+#             */
/*   Updated: 2025/06/09 15:49:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
# define ER_STGS "\033[31mError :\033[0m arguments must be valid.\n"
# define ER_ARGC "\033[31mError :\033[0m invalid arguments size.\n"
# define ER_FRMT "\033[31mError :\033[0m wrong format in arguments\n"

static int	check_args(int argc, char *argv[])
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++j < argc)
	{
		while (argv[j][++i])
		{
			if (!i, (argv[j][i] == '+' || argv[j][i] == '-'))
				continue;
			else if ((argv[j][i] < '0' || argv[j][i] > '9'))
				return (0);
		}
		i = -1;
	}
	return (1);
}

static int	set_stgs(t_stgs *stgs, int argc, char *argv[])
{
	stgs->philo_nb = (int)ft_atol(argv[1]);
	stgs->die_time = ft_atol(argv[2]) * 1000;
	stgs->eat_time = ft_atol(argv[3]) * 1000;
	stgs->sleep_time = ft_atol(argv[4]) * 1000;
	stgs->max_meals = -1;
	if (argc == 6)
		stgs->max_meals = (int)ft_atol(argv[5]);
	if (stgs->philo_nb <= 1 || stgs->die_time < 0 || stgs->eat_time < 0
		|| stgs->sleep_time < 0 || (argc == 6 && stgs->max_meals <= 0))
		return (0);
	return (1);
}

int	parse_settings(t_stgs *stgs, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (printf(ER_ARGC), 0);
	if (!check_args(argc, argv))
		return (printf(ER_FRMT), 0);
	if (!set_stgs(stgs, argc, argv))
		return (printf(ER_STGS), 0);
	debug_stgs(stgs); //DEBUG
	return (1);
}
