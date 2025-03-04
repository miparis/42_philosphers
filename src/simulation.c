/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:30:51 by miparis           #+#    #+#             */
/*   Updated: 2025/03/04 17:26:06 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//Wait for thread creation & syncro start of simulation
//Endless simulation of dinner() until monitor tells

void	*dinner(t_philo *data)
{
	t_philo	*philo;

	philo = data;
	wait_all_threads(philo->g_vars);//wait for all threads to be created
	
	//ver cuando fue la ultima vez que comio
		//check con monitor if simulation has to end
	while (simulation_end(philo->g_vars) == false)
	{
		//is philo full -> Chequear
		if (philo->meals_taken == philo->g_vars->meals_max)
		{
			philo->full = true;
			break ;
		}
		//comer
		//dormir con suleep precise
		//Esribir estado
		
		//pensar
	}
	//simulacion de cena de cada filosofo
	

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
		while (++i < global_vars->philo_nbr)
			thread_handler(&global_vars->philos[i].t_id, dinner, 
				&global_vars->philos[i], CREATE);
	}
	global_vars->start_simulation = get_time();
	printf(B "Simulation started at %ld\n", global_vars->start_simulation);
	set_bool(&global_vars->monitor, &global_vars->threads_ready, true);//threads created
	i = -1;
	while (++i < global_vars->philo_nbr) // Wait for all threads to finish
		thread_handler(&global_vars->philos[i].t_id, NULL, NULL, JOIN);
}

