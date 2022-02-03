/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:46:56 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/09 17:59:24 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_death(t_philo *philo)
{
	long int	curt;

	curt = get_cur_time();
	if (philo->meals[philo->number] >= philo->number_eat
		&& philo->number_eat != -1)
	{
		if (!philo->ended)
			sem_post(philo->finished_meal);
		philo->ended = 1;
	}
	if (curt - philo->last_meal > philo->time_die || philo->n <= 1)
	{
		sem_wait(philo->printer);
		philo->dead = 1;
		printf("%lld %d died\n", get_cur_time(), (int)philo->number);
		exit (0);
	}
	if (philo->dead)
		exit (0);
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
