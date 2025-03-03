/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:46:20 by miparis           #+#    #+#             */
/*   Updated: 2025/03/03 11:51:37 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Wrapper for malloc and its control
void *c_malloc(size_t bytes)
{
	void *rst;

	rst = malloc(bytes);
	if (rst == NULL)
		error_exit(R "Error with malloc\n");
	return (rst);
}	
/*NOTE - Replica of errno messages for mutex related errors*/ 
static void check_mutex(int status)
{
	if (status == 0)
		return ;
	if (status == EINVAL)
		printf(R "Mutex error: Invalid mutex or attributes\n");
	else if (status == ENOMEM)
		printf(R "Mutex error: Not enough memory for another mutex creation\n");
	else if (status == EBUSY)
		printf(R "Mutex error: Mutex is locked or in use\n");
	else if (status == EDEADLK)
		printf(R "Mutex error: Deadlock detected while locking\n");
	else if (status == EPERM)
		printf(R "Mutex error: Thread does not own the mutex\n");
	else
		printf(R "Mutex error: Unknown mutex error: %d\n", status);
}

/*NOTE - Wrapper function & control for all of the mutex related functions*/ 
void	mutex_handler(t_mtx *mutex, t_mutype type)
{
	if (type == INIT)
		check_mutex(pthread_mutex_init(mutex, NULL));
	else if (type == LOCK)
		check_mutex(pthread_mutex_lock(mutex));
	else if (type == UNLOCK)
		check_mutex(pthread_mutex_unlock(mutex));
	else if (type == DESTROY)
		check_mutex(pthread_mutex_destroy(mutex));
	else
		error_exit("Invalid type for mutex use\n");
}

/*NOTE - Replica of errno messages on the thread related functions*/ 
static void	check_thread(int status)
{
	if (status == 0)
		return ;
	if (status == EINVAL)
		printf(R "Thread error: Invalid settings or attributes\n");
	else if (status == EAGAIN)
		printf(R "Thread error: Insufficient resources to create thread\n");
	else if (status == EPERM)
		printf(R "Thread error: Operation not permitted\n");
	else if (status == ESRCH)
		printf(R "Thread error: No thread found with the specified ID\n");
	else
		printf(R "Thread error: Unknown error code %d\n", status);
}

/*NOTE - Wrapper function & control for all of the thread related functions*/ 
void	thread_handler(pthread_t *thread, t_mutype type,
		void *(*funct)(void *), void *data)
{
	if (type == CREATE)
		check_thread(pthread_create(thread, NULL, funct, data));
	else if (type == JOIN)
		check_thread(pthread_join(*thread, NULL));
	else if (type == DETACH)
		check_thread(pthread_detach(*thread));
	else
		error_exit("Invalid type for thread use\n");
}