/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:30:51 by miparis           #+#    #+#             */
/*   Updated: 2025/03/06 17:10:24 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//faltan cosiñas del thiniking
static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
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
	philo->meals_taken++;
	write_status(EATING, philo);
	//precise_usleep(philo->g_vars->time_to_eat, philo->g_vars); //after eating, it sleeps
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
	
	//ver cuando fue la ultima vez que comio
	//check con monitor if simulation has to end
	while (get_state(philo->g_vars) == false)
	{
		//agg monitor
		if (philo->full)//he already eaten all the times he needed
			break ;
		//comer
		eat(philo);
		//dormir con usleep precise
		write_status(SLEEPING, philo); 
		precise_usleep(philo->g_vars->time_to_sleep, philo->g_vars);		
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
	else if (global_vars->philo_nbr == 1)
		printf("Only one philo\n");//run 1 philo simulation
	else
	{
		printf("PHILO NBR: %ld\n", global_vars->philo_nbr);
		while ((++i < global_vars->philo_nbr))
		{
			printf("CREANDO THREADS\n");
			//thread_handler(&global_vars->philos[i].t_id, dinner(&)(), 
				//&global_vars->philos[i], CREATE);
			thread_handler(&global_vars->philos[i].t_id, CREATE, (void *(*)(void *))dinner, global_vars);
				printf("Ya hemos creado los threads\n");
		}
	}
	printf("Ya hemos creado los threads\n");
	global_vars->start_simulation = get_time();
	printf(B "Simulation started at %ld\n", global_vars->start_simulation);
	set_bool(&global_vars->monitor, &global_vars->threads_ready, true);//threads created
	i = -1;
	while (++i < global_vars->philo_nbr) // Wait for all threads to finish
	{
		printf("JOINING\n");	
		thread_handler(&global_vars->philos[i].t_id, JOIN, NULL, NULL);
	}
}

