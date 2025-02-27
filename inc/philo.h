/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:09:35 by miparis           #+#    #+#             */
/*   Updated: 2025/02/27 15:52:54 by miparis          ###   ########.fr       */
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
	t_fork		*right; /*   FORKS        */
	t_fork		*left;
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
	long	start_simulation;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philos;
}				t_global;

/*SECTION -			 main functions     			*/
void	error_exit(const char *error);

/*SECTION -			 init argument functions    	 */
void	parse_args(t_global *global_vars, char **argv);

/* 					Memory & init function			s*/
void	*c_malloc(size_t bytes);
void	thread_handler(pthread_t *thread, t_mutype type,
		void *(*funct)(void *), void *data);
void	mutex_handler(t_mtx *mutex, t_mutype type);

/*!SECTION            TEST						*/
void	print_global_vars(t_global *global);


#endif
