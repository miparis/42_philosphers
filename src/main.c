#include "../inc/philo.h"
// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_max]


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



int	main(int argc, char *argv[])
{
	t_global	global_vars;

	if (argc == 5 || argc == 6)
	{
		parse_args(&global_vars, argv); //parsear
		print_global_vars(&global_vars);
		// init_everything
		//start simulation
		//clean aka a philo dies or everyone is full
	}
	else
	{
		error_exit("Please insert a valid amount of arguments\n");
		//free everything
	}
	return (0);
}








/*
int mails = 0;
pthread_mutex_t mutex;
long unsigned int max_threads = 4;

void *function()
{
	int i = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}
int main(int argc, char *argv[])
{
	pthread_t threads[4];
	long unsigned int i;

	(void)argc;
	(void)argv;
	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < max_threads)
	{
		printf("Thread %ld has started\n", i);
		if (pthread_create(&threads[i], NULL, &function, NULL) != 0)
			printf("Failed to create thread\n");
		i++;
	}
	i = 0;
	while (i < max_threads)
	{
		printf("Thread %ld has ended\n", i);
		if (pthread_join(threads[i], NULL) != 0)
			printf("Failed to join\n");
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Mails received: %d\n", mails);
	return 0;
}*/