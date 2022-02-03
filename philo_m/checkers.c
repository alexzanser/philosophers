/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:46:56 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/09 17:56:47 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_finished_meals(t_philo *philo)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (++i < philo->n)
	{
		if (philo->meals[i] >= philo->number_eat
			&& philo->number_eat != -1)
			c++;
	}
	if (c == philo->n)
	{
		return (1);
	}
	else
		return (0);
}

int	check_death(t_philo *philo)
{
	long int	curt;

	curt = get_cur_time();
	if (check_all_finished_meals(philo))
	{
		pthread_mutex_lock(philo->death);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->death);
	}
	if (curt - philo->last_meal > philo->time_die || philo->n <= 1)
	{
		if (!*philo->dead)
			printf("%lld %d died\n", get_cur_time(), (int)philo->number);
		pthread_mutex_lock(philo->death);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->death);
	}
	if (*philo->dead == 1)
		return (1);
	return (0);
}

int	check_dead(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n)
	{
		if (philo[i].dead)
			return (1);
	}
	return (0);
}
