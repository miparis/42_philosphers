/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:17:53 by miparis           #+#    #+#             */
/*   Updated: 2025/02/27 17:25:32 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void philo_creation(t_global *global_vars)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while(i < global_vars->philo_nbr)
	{
		philo = global_vars->philos + i;
		philo->philo_nbr = i;
		philo->full = false;
		philo->meals_taken = 0;
		philo->g_vars = global_vars;
		//assign forks
		i++;
	}
}


void 	init_structs(t_global *global_vars)
{
	long 	philo_nbr;

	philo_nbr = global_vars->philo_nbr;	
	global_vars->end_simulation = false;
	global_vars->philos = c_malloc(sizeof(t_philo) * philo_nbr);
	global_vars->forks = c_malloc(sizeof(t_fork) * philo_nbr);
	
	//iterator for philo init and forks assigment
	// assign forks with mutex handler
	//assign id
}

