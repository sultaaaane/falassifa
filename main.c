/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:29:21 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/14 21:28:45 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philosophers(t_table *table)
{
	long	i;
	
	i = 0;
	while (i < table->nb_philosophers)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].full = false;
		table->philosophers[i].nb_meals = 0;
		table->philosophers[i].last_meal_time = table->start_time;
		table->philosophers[i].table = table;
		table->philosophers[i].left_fork = &table->forks[i];
		table->philosophers[i].right_fork = &table->forks[(i + 1) % table->nb_philosophers];
		i++;	
	}
}

void init_forks(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nb_philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void init_table(t_table *table)
{
	table->start_time = get_time();
	table->death = false;
	table->end = false;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->start_mutex, NULL);
	pthread_mutex_init(&table->end_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
	init_forks(table);
	init_philosophers(table);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 6 || ac == 5)
	{
		if (!parse(ac, av, &table))
			return (ft_error("Error: invalid arguments\n"));
	}
	else
		return (ft_error("Error: invalid number of arguments\n"));
	return (0);
}
