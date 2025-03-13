/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:36:44 by miparis           #+#    #+#             */
/*   Updated: 2025/03/13 18:48:31 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clean_globals(t_global *g_vars)
{
	t_philo	*philo;
	int 	i;

	i = -1;
	while (++i < g_vars->philo_nbr)
	{
		philo = g_vars->philos + i;
		mutex_handler(&philo->philo_mutex, DESTROY);
	}
	mutex_handler(&g_vars->write, DESTROY);
	mutex_handler(&g_vars->table, DESTROY);
	//mutex_handler(&g_vars->t_ready, DESTROY);
	free(g_vars->forks);
	free(g_vars->philos);
}
