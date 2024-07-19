/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:24:45 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/19 18:15:39 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (nmemb && 18446744073709551615UL / nmemb < size)
		return (NULL);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		ft_bzero(str, 1);
		return (str);
	}
	ft_bzero(str, nmemb * size);
	return (str);
}

int	is_positive(t_table *table)
{
	if (table->nb_philos <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0
		|| table->nb_meals == 0)
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

int	handle_parse(t_table *table)
{
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (1);
	if (table->time_to_die == 2147483648 || table->time_to_eat == 2147483648
		|| table->time_to_sleep == 2147483648 || table->nb_philos > 10000
		|| table->nb_meals == 2147483648 || table->nb_philos == 2147483648)
		return (1);
	return (0);
}
