/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:01:47 by miparis           #+#    #+#             */
/*   Updated: 2025/03/18 11:54:58 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error_exit(const char *error)
{
	printf(R "%s\n" NC, error);
	exit(EXIT_FAILURE);
}

void	wait_all_threads(t_global *g_vars)
{
	if (g_vars->philo_nbr == 1)
		return ;
	while (get_bool(&g_vars->table, &g_vars->threads_ready) == false)
		;
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Error getting time\n");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(long time, t_global *g_vars)
{
	long	start;
	long	transcurred;
	long	remaining;

	start = get_time();
	while (get_time() - start < time)
	{
		if (get_state(g_vars))
			break ;
		transcurred = get_time() - start;
		remaining = time - transcurred;
		if (remaining > 1000)
			usleep(remaining / 2);
		else
		{
			while (get_time() - start < time)
				;
		}
	}
}

void	write_status(t_status status, t_philo *philo)
{
	long	transcurred;

	transcurred = get_time() - (philo->g_vars->start_simulation);
	mutex_handler(&philo->g_vars->write, LOCK);
	if (((status == TAKE_FIRST_FORK) || (status == TAKE_SECOND_FORK))
		&& (!get_state(philo->g_vars)))
		printf(G "%ld" NC " %d has taken a fork\n",
			transcurred, philo->philo_nbr);
	if ((status == EATING) && (!get_state(philo->g_vars)))
		printf(G "%ld" NC " %d is eating\n", transcurred, philo->philo_nbr);
	if ((status == SLEEPING) && (!get_state(philo->g_vars)))
		printf(G "%ld" NC " %d is sleeping\n", transcurred, philo->philo_nbr);
	if ((status == THINKING) && (!get_state(philo->g_vars)))
		printf(G "%ld" NC " %d is thinking\n", transcurred, philo->philo_nbr);
	if (status == DIED)
		printf(G "%ld" NC " %d died\n", transcurred, philo->philo_nbr);
	mutex_handler(&philo->g_vars->write, UNLOCK);
}

/*
void	print_global_vars(t_global *global)
{
	if (!global)
	{
		printf("Global pointer is NULL\n");
		return;
	}
	//Print global variables
	printf(BB"_______________________\n");
	printf("---- Philosopher Number: %ld\n", global->philo_nbr);
	printf("---- Time to Die: %ld ms\n", global->time_to_die / 1000);
	printf("---- Time to Eat: %ld ms\n", global->time_to_eat / 1000);
	printf("---- Time to Sleep: %ld ms\n", global->time_to_sleep / 1000);
	printf("---- Max Meals: %ld\n", global->meals_max);
	printf("---- Start Simulation: %ld\n", global->start_simulation);
	printf("---- End Simulation: %d\n", global->end_simulation);
	printf(BB"_______________________\n"NC);
}

void print_philos(t_global *global_vars)
{
	int i;
	t_philo *philo;

	i = 0;
	printf(BB"\n[Total philosophers: %ld]		\n"NC, global_vars->philo_nbr);
	
	while (i < global_vars->philo_nbr)
	{
		philo = &global_vars->philos[i];

		// Información general del filósofo
		printf(G"\nPhilosopher: %d\n"NC, philo->philo_nbr);
		printf("---- Position in array: %d\n", philo->p_pos);
		printf("---- Meals taken: %ld\n", philo->meals_taken);
		printf("---- Is full: %d\n", philo->full);
		printf("---- First fork ID: %d\n", philo->first->fork_id);
		printf("---- Second fork ID: %d\n", philo->second->fork_id);
		printf(BB"_______________________"NC);
		i++;
	}
}*/