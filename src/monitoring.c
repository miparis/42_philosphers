/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:34:30 by miparis           #+#    #+#             */
/*   Updated: 2025/03/10 19:42:30 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	philo_died(t_philo *philo)
{
	long	transcurred;
	long	t_to_die;


	transcurred = get_time() - get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->g_vars->time_to_die;
	if (get_bool(&philo->philo_mutex, &philo->full)) // philo is full
		return (false);
	if (transcurred > t_to_die) //else he diede
		return (true);
	return (false);
}

bool	threads_count(void *data)
{
	int			ready_count;
	int			i;
	t_global	*g_vars;

	g_vars = (t_global *)data;
	ready_count = 0;
	i = 0;
	while(i < g_vars->philo_nbr)
	{
		mutex_handler(&g_vars->t_ready, LOCK);
		if (g_vars->philos[i].ready)
			ready_count++;
		mutex_handler(&g_vars->t_ready, UNLOCK);
		i++;
	}
	if (ready_count == g_vars->philo_nbr)
		return (true);
	return (false);
}

//Our monitor checks and determinates if the simulation has to end
void	*monitor_dinner(void *data)
{
	t_global	*g_vars;
	int			i;

	g_vars = (t_global *)data;
	i = -1;
	//make sure every philo is running by running threds count endesly
	while (!(threads_count(g_vars)))
		;
	//check constantly if the transcurred time is greater than the time to die
	//if so, we end the simulation
	//also cehck if all the philos have eaten the max amount of times
	while (!(get_state(g_vars)))
	{
		while(++i < g_vars->philo_nbr)
		{
			if (philo_died(g_vars->philos + i))
			{
				set_bool(&g_vars->table, &g_vars->end_simulation, true);
				write_status(DIED, g_vars->philos + i);
			}
		}
	}
	return (NULL);
}
