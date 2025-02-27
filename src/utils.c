/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:01:47 by miparis           #+#    #+#             */
/*   Updated: 2025/02/27 15:53:40 by miparis          ###   ########.fr       */
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