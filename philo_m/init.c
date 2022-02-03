/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:46:56 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/05 17:22:08 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

t_input	*read_input(int argc, char **argv)
{
	int		i;
	t_input	*input;
	t_mutex	*printer;

	input = (t_input *)malloc(sizeof (t_input));
	printer = (t_mutex *) malloc(sizeof (t_mutex));
	input->printer = printer;
	if (!printer)
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

void	init_mutex(t_philo *philo, int n)
{
	int	i;

	i = -1;
	pthread_mutex_init(philo->printer, NULL);
	pthread_mutex_init(philo->death, NULL);
	while (++i < n)
		pthread_mutex_init(&(philo->forks[i]), NULL);
}

void	init_philos(t_philo *philo, t_input *input, t_mutex	*forks)
{
	int		i;
	int		*dead;
	t_mutex	*death;

	dead = (int *)malloc(sizeof (int));
	death = (t_mutex *) malloc(sizeof (t_mutex));
	*dead = 0;
	i = -1;
	while (++i < input->n)
	{
		philo[i].n = input->n;
		philo[i].number = i;
		philo[i].forks = forks;
		philo[i].printer = input->printer;
		philo[i].lf = i;
		philo[i].rf = ((i + philo[i].n - 1) % philo[i].n);
		philo[i].time_die = input->time_die;
		philo[i].time_eat = input->time_eat;
		philo[i].time_sleep = input->time_sleep;
		philo[i].number_eat = input->number_eat;
		philo[i].meals = input->meals;
		philo[i].simulation_start = 0;
		philo[i].dead = dead;
		philo[i].death = death;
	}
}

void	set_simulation_start(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n)
		philo[i].simulation_start = get_cur_time();
}
