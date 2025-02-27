/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:17:53 by miparis           #+#    #+#             */
/*   Updated: 2025/02/27 16:00:49 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

