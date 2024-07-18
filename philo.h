/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:20:56 by mbentahi          #+#    #+#             */
/*   Updated: 2024/07/18 19:13:04 by mbentahi         ###   ########.fr       */
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
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_PHILOSOPHERS 200

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	bool				full;
	long				nb_meals;
	long				last_meal_time;
	t_thread			thread;
	t_mutex				*left_fork;
	t_mutex				*right_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					nb_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nb_meals;
	long				start_time;
	bool				eating;
	bool				death;
	bool				start;
	bool				end;
	t_philo				philo[MAX_PHILOSOPHERS];
	t_mutex				forks[MAX_PHILOSOPHERS];
	t_thread			monitor;
	t_mutex				*start_mtx;
	t_mutex				*print_mtx;
	t_mutex				*meal_mtx;
	t_mutex				*end_mtx;
	t_mutex				*death_mtx;
}						t_table;

int						parse(int ac, char **av, t_table *table);
int						is_positive(t_table *table);
int						ft_error(char *str);
long					get_time(void);
void					print_msg(t_philo *philo, int id, char *msg);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					eating(t_philo *philo);
void					*monitor(void *arg);
bool					check_meal(t_philo *philo);
bool					is_dead(t_philo *philo);
int						l3acha2(t_table *table);
void					*routine(void *args);
bool					did_it_end(t_table *table);
int						ft_usleep(long time_in_ms, t_table *table);
void					clean(t_table *table);

#endif