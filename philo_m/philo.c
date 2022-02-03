/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:46:56 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/09 16:16:59 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

long long int	get_cur_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	smart_sleep(long long time, t_philo *philo)
{
	long long	i;

	i = get_cur_time();
	while (!(*philo->dead))
	{
		if (get_cur_time() - i >= time)
			break ;
		usleep(500);
	}
}

void	*ptread(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->last_meal = philo->simulation_start;
	if (philo->number % 2 == 0)
		smart_sleep(philo->time_eat, philo);
	while (!(*philo->dead))
	{
		take_left_fork(philo);
		take_right_fork(philo);
		try_eat(philo);
		try_sleep(philo);
		try_think(philo);
	}
	return (NULL);
}

int	init_all(t_philo *philo, t_mutex *forks, t_input *input)
{
	if (!philo || !forks || input->n < 1 || input->time_die < 0
		|| input->time_eat < 0 || input->time_sleep < 0 || input->n > 256
		|| (input->number_eat < 0 && input->number_eat != -1))
	{
		printf("Incorrect arguments\n");
		return (1);
	}
	init_philos(philo, input, forks);
	init_mutex(philo, input->n);
	set_simulation_start(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mutex		*forks;
	t_input		*input;
	t_philo		*philo;
	int			i;

	if (argc != 5 && argc != 6)
	{
		printf("Not enough arguments\n");
		return (1);
	}
	input = read_input(argc, argv);
	philo = (t_philo *)malloc(sizeof (t_philo) * (input->n + 1));
	forks = (t_mutex *)malloc(sizeof (t_mutex) * input->n);
	if (!init_all(philo, forks, input))
	{
		i = -1;
		while (++i < input->n)
			pthread_create(&(philo[i].thread_id), NULL, ptread, &(philo[i]));
		i = -1;
		pthread_create(&(philo[input->n].thread_id), NULL, monitor, philo);
		while (++i < input->n + 1)
			pthread_join(philo[i].thread_id, NULL);
	}
	return (0);
}
