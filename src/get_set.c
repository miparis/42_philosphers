/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:17:24 by miparis           #+#    #+#             */
/*   Updated: 2025/03/10 10:23:45 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Setters and getters, aka using mutexes to access shared resources and 
//asigning new values to them avoiding races

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	dest;
	
	mutex_handler(mutex, LOCK);
	dest = *value;
	mutex_handler(mutex, UNLOCK);
	return(dest);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	dest;
	
	mutex_handler(mutex, LOCK);
	dest = *value;
	mutex_handler(mutex, UNLOCK);
	return(dest);
}

bool	get_state(t_global *g_vars)
{
	return(get_bool(&g_vars->monitor, &g_vars->end_simulation));// Cecks if simulation has to end
}