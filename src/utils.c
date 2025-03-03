/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:01:47 by miparis           #+#    #+#             */
/*   Updated: 2025/03/03 12:07:39 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error_exit(const char *error)
{
	printf(R "%s\n" NC, error); //NC restaura el color
	exit(EXIT_FAILURE);
}

//to print values
void	print_global_vars(t_global *global)
{
	if (!global)
	{
		printf("Global pointer is NULL\n");
		return;
	}
	printf("Philosopher Number: %ld\n", global->philo_nbr);
	printf("Time to Die: %ld ms\n", global->time_to_die / 1000);
	printf("Time to Eat: %ld ms\n", global->time_to_eat / 1000);
	printf("Time to Sleep: %ld ms\n", global->time_to_sleep / 1000);
	printf("Max Meals: %ld\n", global->meals_max);
	printf("Start Simulation: %ld\n", global->start_simulation);
	printf("End Simulation: %s\n", global->end_simulation ? "true" : "false");
}

void print_philos(t_global *global_vars)
{
	int i;
	t_philo *philo;

	i = 0;
	printf("Total philosophers: %ld\n", global_vars->philo_nbr);
	
	// Iterar sobre cada filósofo e imprimir sus datos
	while (i < global_vars->philo_nbr)
	{
		philo = &global_vars->philos[i];

		// Información general del filósofo
		printf("->Philosopher: %d\n", philo->philo_nbr);
		printf("  Position in array: %d\n", philo->p_pos);
		printf("  Meals taken: %ld\n", philo->meals_taken);
		printf("  Is full: %s\n", philo->full ? "Yes" : "No");

		// Información sobre los tenedores que tiene asignados
		printf("  First fork ID: %d\n", philo->first->fork_id);
		printf("  Second fork ID: %d\n", philo->second->fork_id);

		printf("\n"); // Espaciado para mejor visualización
		i++; // Avanza al siguiente filósofo
	}
}