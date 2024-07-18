/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:29:21 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/18 17:58:24 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nb_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].full = false;
		table->philo[i].nb_meals = 0;
		table->philo[i].last_meal_time = table->start_time;
		table->philo[i].table = table;
		table->philo[i].right_fork = &table->forks[i + 1];
		table->philo[i].left_fork = &table->forks[i];
		if (table->nb_philos - 1  == i)
		{
			table->philo[i].left_fork = &table->forks[0];
			table->philo[i].right_fork = &table->forks[i];
		}
		i++;
	}
}

void	init_forks(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	init_table(t_table *table)
{
	table->start_time = get_time();
	table->death = false;
	table->end = false;
	table->print_mtx = ft_calloc(sizeof(pthread_mutex_t), 1);
	table->start_mtx = ft_calloc(sizeof(pthread_mutex_t), 1);
	table->end_mtx = ft_calloc(sizeof(pthread_mutex_t), 1);
	table->meal_mtx = ft_calloc(sizeof(pthread_mutex_t), 1);
	table->death_mtx = ft_calloc(sizeof(pthread_mutex_t), 1);
	pthread_mutex_init(table->print_mtx, NULL);
	pthread_mutex_init(table->start_mtx, NULL);
	pthread_mutex_init(table->end_mtx, NULL);
	pthread_mutex_init(table->meal_mtx, NULL);
	pthread_mutex_init(table->death_mtx, NULL);
	init_forks(table);
	init_philosophers(table);
}

void	clean(t_table *table)
{
	int	i;

	i = 0;
	while (table->nb_philos > i)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(table->print_mtx);
	pthread_mutex_destroy(table->start_mtx);
	pthread_mutex_destroy(table->end_mtx);
	pthread_mutex_destroy(table->meal_mtx);
	pthread_mutex_destroy(table->death_mtx);
	free(table->print_mtx);
	free(table->start_mtx);
	free(table->end_mtx);
	free(table->meal_mtx);
	free(table->death_mtx);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 6 || ac == 5)
	{
		if (!parse(ac, av, &table))
			return (ft_error("Error: invalid arguments\n"));
		init_table(&table);
		l3acha2(&table);
	}
	else
		return (ft_error("Error: invalid number of arguments\n"));
	return (clean(&table), 0);
}
