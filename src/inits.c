/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:17:53 by miparis           #+#    #+#             */
/*   Updated: 2025/03/03 12:52:41 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void assign_forks(t_philo *philo, t_fork *fork, int pos)
{
	int		philo_nbr;

	philo_nbr = philo->g_vars->philo_nbr;
	
	philo->first = &fork[pos];
	philo->second = &fork[(pos + 1) % philo_nbr];
	if (philo->p_pos % 2 == 0)
	{
		philo->first = &fork[(pos + 1) % philo_nbr];
		philo->second = &fork[pos];
	}
}

static void philo_creation(t_global *global_vars)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while(++i < global_vars->philo_nbr)
	{
		philo = global_vars->philos + i;
		philo->philo_nbr = i + 1;
		philo->full = false;
		philo->meals_taken = 0;
		philo->p_pos = i;
		philo->g_vars = global_vars;
		assign_forks(philo, global_vars->forks, i);
	}
}

void 	init_structs(t_global *global_vars)
{
	long 	philo_nbr;
	int		i;

	i = -1;
	philo_nbr = global_vars->philo_nbr;	
	global_vars->end_simulation = false;
	global_vars->philos = c_malloc(sizeof(t_philo) * philo_nbr);
	global_vars->forks = c_malloc(sizeof(t_fork) * philo_nbr);
	while (++i < philo_nbr)	//iterator for philo init and forks assigment
	{
		mutex_handler(&global_vars->forks[i].fork, INIT);// assign forks with mutex handler	
		global_vars->forks[i].fork_id = i;//assign id
	}
	philo_creation(global_vars);
	print_philos(global_vars);
}

