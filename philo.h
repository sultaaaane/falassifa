/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:20:56 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/14 21:28:54 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_PHILOSOPHERS 200

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

typedef pthread_t 		t_thread;
typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;


typedef struct s_philosopher
{
	long				id;
	bool				full;
	long 				nb_meals;
	long				last_meal_time;
	t_thread			thread;
	t_mutex				*left_fork;
	t_mutex				*right_fork;
	t_table				*table;
}						t_philosopher;

typedef struct s_table
{
	long				nb_philosophers;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nb_meals;
	long				start_time;
	bool				eating;
	bool				death;
	bool				start;
	bool				end;
	t_philosopher		philosophers[MAX_PHILOSOPHERS];
	t_mutex				forks[MAX_PHILOSOPHERS];
	t_thread			monitor;
	t_mutex				start_mutex;
	t_mutex				print_mutex;
	t_mutex				meal_mutex;
	t_mutex				end_mutex;
}						t_table;

int		parse(int ac, char **av, t_table *table);
int		is_positive(t_table *table);
int		ft_error(char *str);
long	get_time(void);










#endif