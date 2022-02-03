/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:46:56 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/05 17:10:28 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->forks[philo->lf]));
	pthread_mutex_lock((philo->printer));
	if (!*philo->dead)
		printf("%lld %d has taken a fork\n", get_cur_time(), (int)philo->number);
	pthread_mutex_unlock((philo->printer));
}

void	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->forks[philo->rf]));
	pthread_mutex_lock((philo->printer));
	if (!*philo->dead)
		printf("%lld %d has taken a fork\n", get_cur_time(), (int)philo->number);
	pthread_mutex_unlock((philo->printer));
}

void	try_eat(t_philo *philo)
{
	pthread_mutex_lock((philo->printer));
	if (!*philo->dead)
		printf("%lld %d is eating\n", get_cur_time(), (int)philo->number);
	philo->meals[philo->number] += 1;
	pthread_mutex_unlock((philo->printer));
	philo->last_meal = get_cur_time();
	smart_sleep(philo->time_eat, philo);
	pthread_mutex_unlock(&(philo->forks[philo->lf]));
	pthread_mutex_unlock(&(philo->forks[philo->rf]));
}

void	try_sleep(t_philo *philo)
{
	pthread_mutex_lock((philo->printer));
	if (!*philo->dead)
		printf("%lld %d is sleeping\n", get_cur_time(), (int)philo->number);
	pthread_mutex_unlock((philo->printer));
	smart_sleep(philo->time_sleep, philo);
}

void	try_think(t_philo *philo)
{
	pthread_mutex_lock((philo->printer));
	if (!*philo->dead)
		printf("%lld %d is thinking\n", get_cur_time(), (int)philo->number);
	pthread_mutex_unlock((philo->printer));
}
