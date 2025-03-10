/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:34:30 by miparis           #+#    #+#             */
/*   Updated: 2025/03/10 11:58:43 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor_dinner(void *data)
{
	
}


//Our monitor checks and determinates if the simulation has to end
void	*monitor_dinner(void *data)
{
	t_global	*g_vars;

	g_vars = (t_global *)data;

	//make sure every philo is running
	
	//check constantly if the transcurred time is greater than the time to die
	//if so, we end the simulation
	//also cehck if all the philos have eaten the max amount of times
	while (1)
	{
	}
	return (NULL);
}