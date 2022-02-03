/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:46:56 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/05 17:17:09 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_input
{
	int			n;
	int			time_eat;
	int			time_sleep;
	int			time_die;
	int			*meals;
	int			number_eat;
	t_mutex		*printer;
}	t_input;

typedef struct s_philo
{
	int			id;
	int			n;
	int			number;
	t_mutex		*forks;
	t_mutex		*death;
	t_mutex		*printer;
	pthread_t	thread_id;
	int			lf;
	int			rf;
	int			time_eat;
	int			time_die;
	int			*meals;
	int			time_sleep;
	int			number_eat;
	int			*dead;
	long int	simulation_start;
	long int	started;
	long int	last_meal;
}	t_philo;

int				ft_atoi(const char *str);
void			*ft_calloc( size_t number, size_t size );
void			ft_bzero(void *s, size_t n);
int				check_dead(t_philo *philo);
int				check_all_finished_meals(t_philo *philo);
int				check_death(t_philo *philo);
void			set_simulation_start(t_philo *philo);
void			smart_sleep(long long time, t_philo *philo);
t_input			*read_input(int argc, char **argv);
void			init_mutex(t_philo *philo, int n);
void			init_philos(t_philo *philo, t_input *input, t_mutex	*forks);
long long int	get_cur_time(void);
void			*monitor(void *args);
void			take_left_fork(t_philo *philo);
void			take_right_fork(t_philo *philo);
void			try_eat(t_philo *philo);
void			try_sleep(t_philo *philo);
void			try_think(t_philo *philo);
#endif
