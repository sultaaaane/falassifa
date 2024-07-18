/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3acha2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:22:27 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/18 18:41:52 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	did_it_end(t_table *table)
{
	if (table->nb_meals == 0)
		return (true);
	pthread_mutex_lock(table->end_mtx);
	if (table->end == true)
		return (pthread_mutex_unlock(table->end_mtx), true);
	pthread_mutex_unlock(table->end_mtx);
	return (false);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(10, philo->table);
	if (philo->table->nb_philos == 1)
	{
		if (did_it_end(philo->table))
			return (NULL);
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, philo->id, " has taken a fork");
		pthread_mutex_unlock(philo->left_fork);
		ft_usleep(philo->table->time_to_die, philo->table);
		pthread_mutex_lock(philo->table->print_mtx);
		print_msg(philo, philo->id, "Died");
		pthread_mutex_unlock(philo->table->print_mtx);
		return (NULL);
	}
	while (!did_it_end(philo->table))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	l3acha2(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philo[i].thread, NULL, routine,
				&table->philo[i]))
			return (ft_error("Error: pthread_create failed"));
		i++;
	}
	if (pthread_create(&table->monitor, NULL, monitor, &table->philo))
		return (ft_error("Error: pthread_create failed"));
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			return (ft_error("Error: pthread_join failed"));
		i++;
	}
	if (pthread_join(table->monitor, NULL))
		return (ft_error("Error: pthread_join failed"));
	return (0);
}

int	ft_usleep(long time_in_ms, t_table *table)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
	{
		if (did_it_end(table))
			return (0);
		usleep(500);
	}
	return (0);
}
