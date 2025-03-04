/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:09:35 by miparis           #+#    #+#             */
/*   Updated: 2025/03/04 17:26:28 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>
#include <errno.h>

// Define Colors
# define G	"\033[1;32m"  // Bold Green
# define Y	"\033[0;33m"  // Non-bold Yellow
# define R	"\033[0;31m"  // Regular Red
# define BB	"\033[1;34m"  // Bold Blue
# define P	"\033[1;35m"  // Bold Purple
# define B	"\033[1m"  	// Bold Text
# define NC	"\033[0m"  	// No Color (Resets color and style)

# ifndef MS
# define MS 60000
# endif

typedef pthread_mutex_t t_mtx;
typedef struct global t_global;

typedef enum e_mutype
{
	CREATE,
	INIT,
	JOIN,
	LOCK,
	UNLOCK,
	DETACH,
	DESTROY
}	t_mutype;


typedef struct fork
{
	t_mtx 	fork;
	int 	fork_id;	
}				t_fork;

typedef struct philo
{
	int			philo_nbr;
	long		meals_taken;
	long 		last_meal_time;
	bool		full; // set to true if meals taken == meals_max
	int			p_pos; // position in the "table"
	t_fork		*first; /*   FORKS        */
	t_fork		*second;
	pthread_t	t_id; // ID del hilo
	t_global	*g_vars;
}				t_philo;

typedef struct global
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals_max;
	long	start_simulation; //Time of the start of the simulation
	bool	threads_ready; //Wait for threads to be created
	bool	end_simulation; //For the monitor
	t_mtx	monitor; //Avoid races while reading the g_vars 
	t_mtx	write;
	t_fork	*forks;
	t_philo	*philos;
}				t_global;

/*SECTION -			 Utils    						*/
void	error_exit(const char *error);
void	wait_all_threads(t_global *g_vars);
long	get_time(void);
void	precise_usleep(long time, t_global *g_vars);

/*SECTION -			 init argument functions    	*/
void	parse_args(t_global *global_vars, char **argv);

/* 					Memory & init functions			*/
void	*c_malloc(size_t bytes);
void	thread_handler(pthread_t *thread, t_mutype type,
		void *(*funct)(void *), void *data);
void	mutex_handler(t_mtx *mutex, t_mutype type);
void 	init_structs(t_global *global_vars);

/*					Getters & setters				*/
bool	get_state(t_global *g_vars);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);


/*!SECTION            TEST						    */
void	print_global_vars(t_global *global);
void	print_philos(t_global *global_vars);


#endif
