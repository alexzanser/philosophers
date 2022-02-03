/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:46:56 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/04 22:00:42 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_input
{
	int			n;
	int			time_eat;
	int			time_sleep;
	int			time_die;
	int			*meals;
	int			number_eat;
	sem_t		*forks;
	sem_t		*printer;
}	t_input;

typedef struct s_philo
{
	int			id;
	int			n;
	int			number;
	sem_t		*forks;
	sem_t		*printer;
	pthread_t	thread_id;
	sem_t		*finished_meal;
	int			lf;
	int			rf;
	int			time_eat;
	int			time_die;
	int			*meals;
	int			time_sleep;
	int			number_eat;
	int			ended;
	int			dead;
	int			is_eating;
	pid_t		pid[5];
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
void			init_philos(t_philo *philo, t_input *input);
long long int	get_cur_time(void);
void			*monitor(void *args);
void			take_left_fork(t_philo *philo);
void			take_right_fork(t_philo *philo);
void			try_eat(t_philo *philo);
void			try_sleep(t_philo *philo);
void			try_think(t_philo *philo);
int				ft_error(void);
void			wait_for_end(t_philo *philo, t_input *input, pid_t	*pid);
#endif
