#include "../inc/philo.h"
// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_max]

int	main(int argc, char *argv[])
{
	t_global	global_vars;

	if (argc == 5 || argc == 6)
	{
		parse_args(&global_vars, argv); //parsear
		//print_global_vars(&global_vars);
		init_structs(&global_vars); //init
		simulation(&global_vars);//start simulation
		//clean aka a philo dies or everyone is full
		clean_globals(&global_vars);
	}
	else
	{
		error_exit("Please insert a valid amount of arguments\n");
		clean_globals(&global_vars);
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