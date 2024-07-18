/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:01:34 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/18 16:46:12 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, int id, char *msg)
{
	if (did_it_end(philo->table))
		return ;
	pthread_mutex_lock(philo->table->print_mtx);
	if (philo->table->death)
	{
		pthread_mutex_unlock(philo->table->print_mtx);
		return ;
	}
	printf("%ld %d %s\n", get_time() - philo->table->start_time, id, msg);
	pthread_mutex_unlock(philo->table->print_mtx);
}

void	thinking(t_philo *philo)
{
	if (did_it_end(philo->table))
		return ;
	print_msg(philo, philo->id, "is thinking");
	if (philo->table->nb_philos % 2)
		ft_usleep(1, philo->table);
}

void	sleeping(t_philo *philo)
{
	if (did_it_end(philo->table))
		return ;
	print_msg(philo, philo->id, "is sleeping");
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	eating(t_philo *philo)
{
	if (did_it_end(philo->table))
		return ;
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, philo->id, " has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, philo->id, "has taken a fork");
	print_msg(philo, philo->id, "is eating");
	pthread_mutex_lock(philo->table->meal_mtx);
	philo->nb_meals++;
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(philo->table->meal_mtx);
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
