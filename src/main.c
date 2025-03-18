/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:57:30 by miparis           #+#    #+#             */
/*   Updated: 2025/03/18 11:22:30 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	t_global	global_vars;

	if (argc == 5 || argc == 6)
	{
		parse_args(&global_vars, argv);
		if (global_vars.meals_max == 0)
		{
			printf("No simulation needed\n");
			return (0);
		}
		init_structs(&global_vars);
		simulation(&global_vars);
		clean_globals(&global_vars);
	}
	else
	{
		error_exit("Please insert a valid amount of arguments\n");
		clean_globals(&global_vars);
	}
	return (0);
}
