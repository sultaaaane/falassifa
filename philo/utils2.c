/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:26:39 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/19 16:29:01 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	size_check(long result)
{
	if (result > INT_MAX || result < INT_MIN)
		return (1);
	return (0);
}

static int	check_overflow(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '-')
		i++;
	while (str[i] && str[i] == '0')
		i++;
	if (ft_strlen(&str[i]) > 12)
		return (1);
	return (0);
}

long	ft_enhanced_atoi(char *str)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
		if (str[i] == ' ' || str[i] == '\0')
			return (2147483648);
	}
	while (ft_isdigit(str[i]))
		result = result * 10 + (str[i++] - '0');
	if (size_check(result))
		return (2147483648);
	if (check_overflow(str))
		return (2147483648);
	return (result * sign);
}

int	ft_isall_digit(char *str)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			if (sign)
				return (0);
			sign = 1;
			i++;
		}
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
