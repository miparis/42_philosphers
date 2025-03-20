/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:30:51 by miparis           #+#    #+#             */
/*   Updated: 2025/03/20 10:57:07 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_bool(&philo->philo_mutex, &philo->ready, true);
	wait_all_threads(philo->g_vars);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
	precise_usleep(philo->g_vars->time_to_die / 1000, philo->g_vars);
	return (NULL);
}

void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
	usleep(200);
}

static void	eat(t_philo *philo)
{
	mutex_handler(&philo->first->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	mutex_handler(&philo->second->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
	philo->meals_taken++;
	write_status(EATING, philo);
	precise_usleep(philo->g_vars->time_to_eat / 1000, philo->g_vars);
	if (philo->g_vars->meals_max > 0
		&& (philo->meals_taken == philo->g_vars->meals_max))
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handler(&philo->first->fork, UNLOCK);
	mutex_handler(&philo->second->fork, UNLOCK);
}

void	*dinner(t_philo *data)
{
	t_philo	*philo;

	philo = data;
	wait_all_threads(philo->g_vars);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
	threads_count(philo->g_vars);
	if (philo->philo_nbr % 2)
	{
		if (philo->g_vars->time_to_eat > philo->g_vars->time_to_die)
			precise_usleep(philo->g_vars->time_to_die / 1000, philo->g_vars);
		else
			precise_usleep(philo->g_vars->time_to_eat / 1000, philo->g_vars);
	}
	while (get_state(philo->g_vars) == false)
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->g_vars->time_to_sleep / 1000, philo->g_vars);
		thinking(philo);
	}
	return (NULL);
}

void	simulation(t_global *g_vars)
{
	int	i;

	i = -1;
	if (g_vars->philo_nbr == 1)
	{
		thread_handler(&g_vars->philos[0].t_id,
			CREATE, one_philo, &g_vars->philos[0]);
	}
	else
	{
		while ((++i < g_vars->philo_nbr))
		{
			thread_handler(&g_vars->philos[i].t_id,
				CREATE, (void *)dinner, &g_vars->philos[i]);
			g_vars->philos[i].ready = true;
		}
	}
	g_vars->start_simulation = get_time();
	thread_handler(&g_vars->monitor, CREATE, monitor_dinner, g_vars);
	set_bool(&g_vars->table, &g_vars->threads_ready, true);
	i = -1;
	while (++i < g_vars->philo_nbr)
		thread_handler(&g_vars->philos[i].t_id, JOIN, NULL, NULL);
	set_bool(&g_vars->table, &g_vars->end_simulation, true);
	thread_handler(&g_vars->monitor, JOIN, NULL, NULL);
}
