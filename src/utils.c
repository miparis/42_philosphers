/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:01:47 by miparis           #+#    #+#             */
/*   Updated: 2025/03/10 11:29:25 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error_exit(const char *error)
{
	printf(R "%s\n" NC, error); //NC restaura el color
	exit(EXIT_FAILURE);
}
//This function will endlessly check for the state of threads 
//ready until all the threads are created
void	wait_all_threads(t_global *g_vars)
{
	while (get_bool(&g_vars->table, &g_vars->threads_ready) == false)
		return ;
}

long	get_time(void)
{
	struct timeval	time;
	long			milliseconds;
	long			seconds;

	if (gettimeofday(&time, NULL))
		error_exit("Error getting time\n");
	seconds = time.tv_sec * 1000;//pasamos segundos y microsegundos a milisegundos
	milliseconds = time.tv_usec / 1000;
	return (seconds + milliseconds);
}

void	precise_usleep(long time, t_global *g_vars)
{
	long	start;
	long	transcurred;
	long	remaining;

	start = get_time(); //Obtener tiempo de inicio
	while (get_time() - start < time) //nos mantenemos en el bucle hasta que time == 0
	{
		if (get_state(g_vars))
			break; //salimos si ya no hay simulación
		transcurred = get_time() - start;
		remaining = time - transcurred;
		if (remaining > 1000) //Si queda más de 1000 μs (1 ms), llamamos a usleep() con la mitad del tiempo restante para reducir la carga de la CPU.
			usleep(remaining / 2);
		else
		{
			//Si el tiempo restante es muy pequeño, entramos en un busy-waiting loop para mayor precisión.
			while (get_time() - start < time);
		}
	}
}

void write_status(t_status status, t_philo *philo)
{
    long transcurred;

    transcurred = get_time() - philo->g_vars->start_simulation;
    mutex_handler(&philo->g_vars->write, LOCK);
    if (((status == TAKE_FIRST_FORK) || (status == TAKE_SECOND_FORK)) 
        && (!get_state(philo->g_vars)))
        printf(G "%ld" NC " [%d] has taken a fork\n", transcurred, philo->philo_nbr);

    if ((status == EATING) && (!get_state(philo->g_vars)))
        printf(G "%ld" NC " [%d] is eating\n", transcurred, philo->philo_nbr);

    if ((status == SLEEPING) && (!get_state(philo->g_vars)))
        printf(G "%ld" NC " [%d] is sleeping\n", transcurred, philo->philo_nbr);

    if ((status == THINKING) && (!get_state(philo->g_vars)))
        printf(G "%ld" NC " [%d] is thinking\n", transcurred, philo->philo_nbr);

    if (status == DIED)
        printf(G "%ld" NC " [%d] died\n", transcurred, philo->philo_nbr);

    mutex_handler(&philo->g_vars->write, UNLOCK);
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
	//printf("Start Simulation: %ld\n", global->start_simulation);
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