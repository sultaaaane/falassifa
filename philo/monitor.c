/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:27:29 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/19 14:46:15 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->table->meal_mtx);
	time = get_time() - philo->last_meal_time;
	pthread_mutex_unlock(philo->table->meal_mtx);
	if (time >= philo->table->time_to_die + 1)
		return (true);
	return (false);
}

bool	check_meal(t_philo *philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	pthread_mutex_lock(philo->table->meal_mtx);
	if (philo[0].table->nb_meals == -1)
		return (pthread_mutex_unlock(philo->table->meal_mtx), false);
	pthread_mutex_unlock(philo->table->meal_mtx);
	while (philo[0].table->nb_philos > i)
	{
		pthread_mutex_lock(philo->table->meal_mtx);
		if (philo[i].nb_meals >= philo[i].table->nb_meals)
			count++;
		pthread_mutex_unlock(philo->table->meal_mtx);
		i++;
	}
	if (count == philo[0].table->nb_philos)
	{
		pthread_mutex_lock(philo->table->end_mtx);
		philo[0].table->end = true;
		pthread_mutex_unlock(philo->table->end_mtx);
		return (true);
	}
	return (false);
}

bool	check_is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].table->nb_philos)
	{
		if (is_dead(&philo[i]))
		{
			print_msg(&philo[i], philo[i].id, "Died");
			pthread_mutex_lock(philo->table->end_mtx);
			philo[i].table->end = true;
			pthread_mutex_unlock(philo->table->end_mtx);
			return (true);
		}
		i++;
	}
	return (false);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_is_dead(philo) || check_meal(philo))
			break ;
	}
	return (NULL);
}
