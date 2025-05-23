/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:46:10 by alde-abr          #+#    #+#             */
/*   Updated: 2025/05/16 22:16:03 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
# define ER_STGS "\033[31mError :\033[0m arguments must be valid.\n"
# define ER_ARGC "\033[31mError :\033[0m invalid arguments size.\n"

static int	set_stgs(t_stgs *stgs, int argc, char *argv[])
{
	stgs->philo_nb = ft_atoi_lmt(argv[1]);
	stgs->die_time = ft_atoi_lmt(argv[2]);
	stgs->eat_time = ft_atoi_lmt(argv[3]);
	stgs->sleep_time = ft_atoi_lmt(argv[4]);
	stgs->max_meals = -1;
	if (argc == 6)
		stgs->max_meals = ft_atoi_lmt(argv[5]);
	if (stgs->philo_nb <= 1 || stgs->die_time < 0 || stgs->eat_time < 0
		|| stgs->sleep_time < 0 || (argc == 6 && stgs->max_meals <= 0))
		return (0);
	return (1);
}

int	parse_simulation(t_sim *sim, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (printf(ER_ARGC), 0);
	if (!set_stgs(&sim->stgs, argc, argv))
		return (printf(ER_STGS), 0);
	debug_stgs(&sim->stgs);
	return (1);
}
