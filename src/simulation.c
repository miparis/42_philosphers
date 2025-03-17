/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:30:51 by miparis           #+#    #+#             */
/*   Updated: 2025/03/17 11:57:38 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->g_vars);
	threads_count(philo->g_vars);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
	write_status(TAKE_FIRST_FORK, &philo->g_vars->philos[0]);
	while (philo_died(philo) == false)
	{
		usleep(philo->g_vars->time_to_die / 1000);
		set_bool(&philo->g_vars->table, &philo->g_vars->end_simulation, true);
	}
	write_status(DIED, philo);
	return (NULL);
}

void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
	usleep(200);
}
//Wait for thread creation & syncro start of simulation
//Endless simulation of dinner() until monitor tells
static void	eat(t_philo *philo)
{
	// we grab each fork and indicate the action
	mutex_handler(&philo->first->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	mutex_handler(&philo->second->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time()); //to check if the philo died
	//printf("Last meal after: %ld\n", philo->last_meal_time);
	philo->meals_taken++;
	write_status(EATING, philo);
	precise_usleep(philo->g_vars->time_to_eat / 1000, philo->g_vars); //after eating, it sleeps
	if (philo->g_vars->meals_max > 0 &&
		(philo->meals_taken == philo->g_vars->meals_max))
		set_bool(&philo->philo_mutex, &philo->full, true); // we change the state if we reached the max of meals
	mutex_handler(&philo->first->fork, UNLOCK);//liberamos tenedores
	mutex_handler(&philo->second->fork, UNLOCK);
}

void	*dinner(t_philo *data)
{
	t_philo	*philo;

	philo = data;
	wait_all_threads(philo->g_vars);//wait for all threads to be created
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());//set the last meal time of the incoming philo
	threads_count(philo->g_vars);//check if all threads are ready

	//desyncro the philos to avoid starvations
	if (philo->philo_nbr % 2)
	{
		if (philo->g_vars->time_to_eat > philo->g_vars->time_to_die)
			precise_usleep(philo->g_vars->time_to_die / 1000, philo->g_vars);
		else
			precise_usleep(philo->g_vars->time_to_eat / 1000, philo->g_vars);

	}
	//check with monitor if simulation has to end due to philo died or all philos are full
	while (get_state(philo->g_vars) == false)
	{
		//agg monitor
		if (philo->full)//he already eaten all the times he needed
			break ;
		//comer
		eat(philo);
		//dormir con usleep precise
		write_status(SLEEPING, philo); 
		precise_usleep(philo->g_vars->time_to_sleep / 1000, philo->g_vars);		
		//pensar
		thinking(philo);
	}
	return (NULL);
}

/*If nbr of meals == 0 , there is no simulation*/
/*Handle 1 philo only a.k.a no shared resources*/
/*Create threads a.k.a philos and assign te forks for the routine*/
/*Create monitor to check when a simulation has to stop == philo(dead) meals_max == FULL*/
/*Syncro the creation of threads(to avoid deadlock or races) and start of everything for dinners*/
void	simulation(t_global *global_vars)
{
	int i;

	i = -1;
	if (global_vars->meals_max == 0)
	{
		printf("No simulation needed\n");
		return ; //return to clean eveything
	}
	if (global_vars->philo_nbr == 1)
	{
		thread_handler(&global_vars->philos[0].t_id, CREATE, one_philo, &global_vars->philos[0]);
		global_vars->philos[0].ready = true;
	}
	else
	{
		while ((++i < global_vars->philo_nbr))
		{
			//printf("---Thread created -> [%d]\n", i);
			thread_handler(&global_vars->philos[i].t_id, CREATE, (void *)dinner, &global_vars->philos[i]);
			global_vars->philos[i].ready = true;
		}
	}
	global_vars->start_simulation = get_time();
	//printf(B G"Simulation started at %ld\n" NC, global_vars->start_simulation);
	thread_handler(&global_vars->monitor, CREATE, monitor_dinner, global_vars);
	set_bool(&global_vars->table, &global_vars->threads_ready, true);//threads created
	i = -1;
	while (++i < global_vars->philo_nbr) // Wait for all threads to finish
		thread_handler(&global_vars->philos[i].t_id, JOIN, NULL, NULL);
	//all philos are full
	set_bool(&global_vars->table, &global_vars->end_simulation, true);
	thread_handler(&global_vars->monitor, JOIN, NULL, NULL);
}
