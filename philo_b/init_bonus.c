/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:46:56 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/09 18:58:05 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_input	*read_input(int argc, char **argv)
{
	int		i;
	t_input	*input;

	input = (t_input *)malloc(sizeof (t_input));
	if (!input)
		return (NULL);
	input->n = ft_atoi(argv[1]);
	input->time_die = ft_atoi(argv[2]);
	input->time_eat = ft_atoi(argv[3]);
	input->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->number_eat = ft_atoi(argv[5]);
	else
		input->number_eat = -1;
	input->meals = (int *)ft_calloc(input->n, sizeof(int));
	i = -1;
	while (++i < input->n)
		input->meals[i] = 0;
	return (input);
}

void	init_philos2(t_philo *philo, t_input *input)
{
	int		i;

	i = -1;
	while (++i < input->n)
	{
		philo[i].n = input->n;
		philo[i].number = i;
		philo[i].lf = i;
		philo[i].rf = ((i + philo[i].n - 1) % philo[i].n);
		philo[i].time_die = input->time_die;
		philo[i].time_eat = input->time_eat;
		philo[i].time_sleep = input->time_sleep;
		philo[i].number_eat = input->number_eat;
		philo[i].meals = input->meals;
		philo[i].simulation_start = 0;
		philo[i].dead = 0;
		philo[i].ended = 0;
		philo[i].is_eating = 0;
	}
}

void	init_philos(t_philo *philo, t_input *input)
{
	int		i;
	sem_t	*forks;
	sem_t	*printer;
	sem_t	*finished;

	i = -1;
	sem_unlink("/forks");
	sem_unlink("/printer");
	sem_unlink("/finished");
	finished = sem_open("/finished", O_CREAT, S_IRWXU, input->n);
	forks = sem_open("/forks", O_CREAT, S_IRWXU, input->n);
	printer = sem_open("/printer", O_CREAT, S_IRWXU, 1);
	while (++i < input->n)
	{
		philo[i].printer = printer;
		philo[i].forks = forks;
		philo[i].finished_meal = finished;
	}
	init_philos2(philo, input);
}

void	set_simulation_start(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n)
		philo[i].simulation_start = get_cur_time();
}

void	*monitor(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	smart_sleep(philo->time_eat, philo);
	while (!check_death(philo))
		(void) args;
	exit(1);
}
