/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:08:21 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/19 15:46:36 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_positive(t_table *table)
{
	if (table->nb_philos <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0 || table->nb_meals == 0)
		return (0);
	return (1);
}

int	parse_helper(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_isall_digit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int handle_parse(t_table *table)
{
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (1);
	if (table->time_to_die == 2147483648 || table->time_to_eat == 2147483648
		|| table->time_to_sleep == 2147483648 || table->nb_philos >= 200 || table->nb_meals == 2147483648)
		return (1);
	return (0);
}

int	parse(int ac, char **av, t_table *table)
{
	if (parse_helper(ac, av) == 0)
		return (0);
	table->nb_philos = ft_enhanced_atoi(av[1]);
	table->time_to_die = ft_enhanced_atoi(av[2]);
	table->time_to_eat = ft_enhanced_atoi(av[3]);
	table->time_to_sleep = ft_enhanced_atoi(av[4]);
	if (ac == 6)
	{
		table->nb_meals = ft_enhanced_atoi(av[5]);
		if (table->nb_meals < 0)
			return (0);
	}
	else
		table->nb_meals = -1;
	if (!is_positive(table))
		return (0);
	if (handle_parse(table))
		return (0);
	return (1);
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (-1);
}

long	get_time(void)
{
	struct timeval	time;
	long			ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec * 1e3) + (time.tv_usec / 1e3);
	return (ret);
}
