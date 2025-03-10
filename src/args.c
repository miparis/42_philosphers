/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:13:04 by miparis           #+#    #+#             */
/*   Updated: 2025/03/10 10:45:01 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
//check if the string has only valid digits
static const char *check_str(const char *str)
{
	int			len;
	const char	*nbr_str;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Arguments can be positive nbrs only\n");
	if (!is_digit(*str))
		error_exit("Argument with incorrect digits\n");
	nbr_str = str;
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (len > 10)
		error_exit("Value of argument surpasses INT_MAX\n");
	return (nbr_str);
}

//convert to long to assign 
static long	ft_atol(const char *str)
{
	long nbr;

	nbr = 0;
	str = check_str(str); //check string
	while (is_digit(*str))
	{
		nbr = (nbr * 10 ) + (*str - '0');
		str++;
	}
	if (nbr > INT_MAX)
				error_exit("Value of argument surpasses INT_MAX\n");
	return (nbr);
}
// init all the global vars with the corresponding format
// We convert miliseconds to microsecs with (ft_atol() * 1e3)
void 	parse_args(t_global *global_vars, char **argv)
{
	global_vars->end_simulation = false;
	global_vars->philo_nbr = ft_atol(argv[1]);
	global_vars->time_to_die = ft_atol(argv[2]) * 1000; // milisegundos a microsegundos
	global_vars->time_to_eat = ft_atol(argv[3]) * 1000;
	global_vars->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		global_vars->meals_max = ft_atol(argv[5]);
	else
		global_vars->meals_max = -1;
	//print_global_vars(global_vars);
	if (global_vars->time_to_die < MS 
		|| global_vars->time_to_eat < MS
		|| global_vars->time_to_sleep < MS)
		error_exit("Min time 60ms for time arguments\n");
	global_vars->start_simulation = 0;
}
