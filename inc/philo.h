/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:09:35 by miparis           #+#    #+#             */
/*   Updated: 2025/03/19 11:40:33 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <errno.h>

# define G	"\033[1;32m"
# define Y	"\033[0;33m"
# define R	"\033[0;31m"
# define BB	"\033[1;34m"
# define P	"\033[1;35m"
# define B	"\033[1m"
# define NC	"\033[0m"

# ifndef MS
#  define MS 60000
# endif

typedef	pthread_mutex_t			t_mtx;
typedef struct	s_global		t_global;
typedef enum	e_mutype		t_mutype;
typedef enum	e_status		t_status;
typedef struct	s_fork			t_fork;
typedef struct	s_philo			t_philo;

enum e_mutype
{
	CREATE,
	INIT,
	JOIN,
	LOCK,
	UNLOCK,
	DETACH,
	DESTROY
};

enum e_status
{
	DIED,
	SLEEPING,
	EATING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK
};

struct s_fork
{
	t_mtx	fork;
	int		fork_id;
};

struct s_philo
{
	int			philo_nbr;
	long		meals_taken;
	long		last_meal_time;
	bool		ready;
	bool		full;
	int			p_pos;
	t_fork		*first;
	t_fork		*second;
	t_mtx		philo_mutex;
	pthread_t	t_id;
	t_global	*g_vars;
};

struct s_global
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_max;
	long		start_simulation;
	bool		threads_ready;
	bool		end_simulation;
	t_mtx		t_ready;
	t_mtx		table;
	t_mtx		write;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;
};

/*SECTION -			 Utils    						*/
void	error_exit(const char *error);
void	wait_all_threads(t_global *g_vars);
long	get_time(void);
void	precise_usleep(long time, t_global *g_vars);
void	write_status(t_status status, t_philo *philo);

/*SECTION -			 Simulation functions			*/
void	simulation(t_global *global_vars);
void	*dinner(t_philo *data);
void	thinking(t_philo *philo);
bool	philo_died(t_philo *philo);
void	thinking_fairness(t_philo *philo, bool simul);

/*SECTION -			 init argument functions    	*/
void	parse_args(t_global *global_vars, char **argv);

/* 					Memory & init functions			*/
void	*c_malloc(size_t bytes);
void	thread_handler(pthread_t *thread, t_mutype type,
			void *(*funct)(void *), void *data);
void	mutex_handler(t_mtx *mutex, t_mutype type);
void	init_structs(t_global *global_vars);

/*					Monitoring						*/
void	*monitor_dinner(void *data);
bool	threads_count(void *data);

/*					Getters & setters				*/
bool	get_state(t_global *g_vars);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);

/*!SECTION 				Free						*/
void	clean_globals(t_global *g_vars);

/*!SECTION            TEST						    */
void	print_global_vars(t_global *global);
void	print_philos(t_global *global_vars);

#endif
