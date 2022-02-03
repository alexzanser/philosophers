/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 21:42:55 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/09 18:37:21 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_left_fork(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->printer);
	printf("%lld %d has taken a fork\n", get_cur_time(), (int)philo->number);
	sem_post(philo->printer);
}

void	take_right_fork(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->printer);
	printf("%lld %d has taken a fork\n", get_cur_time(), (int)philo->number);
	sem_post(philo->printer);
}

void	try_eat(t_philo *philo)
{
	philo->last_meal = get_cur_time();
	sem_wait(philo->printer);
	printf("%lld %d is eating\n", get_cur_time(), (int)philo->number);
	sem_post(philo->printer);
	smart_sleep(philo->time_eat, philo);
	philo->meals[philo->number] += 1;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	try_sleep(t_philo *philo)
{
	sem_wait(philo->printer);
	printf("%lld %d is sleeping\n", get_cur_time(), (int)philo->number);
	sem_post(philo->printer);
	smart_sleep(philo->time_sleep, philo);
}

void	try_think(t_philo *philo)
{
	sem_wait(philo->printer);
	printf("%lld %d is thinking\n", get_cur_time(), (int)philo->number);
	sem_post(philo->printer);
}
