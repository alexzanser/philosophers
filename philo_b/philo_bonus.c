/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:46:56 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/09 19:12:10 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

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
	while (!(philo->dead))
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
	pthread_create(&philo->thread_id, NULL, monitor, philo);
	pthread_detach(philo->thread_id);
	while (!check_death(philo))
	{
		take_left_fork(philo);
		take_right_fork(philo);
		try_eat(philo);
		try_sleep(philo);
		try_think(philo);
	}
	exit (0);
}

int	init_all(t_philo *philo, t_input *input)
{
	if (!philo || input->n < 1 || input->time_die < 0 || input->time_eat < 0
		|| input->time_sleep < 0 || input->n > 256
		|| (input->number_eat < 0 && input->number_eat != -1))
	{
		printf("Incorrect arguments\n");
		return (1);
	}
	init_philos(philo, input);
	set_simulation_start(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_input		*input;
	t_philo		*philo;
	pid_t		*pid;
	int			i;

	if (argc != 5 && argc != 6)
		return (ft_error());
	input = read_input(argc, argv);
	philo = (t_philo *)malloc(sizeof (t_philo) * input->n);
	if (!init_all(philo, input))
	{
		i = -1;
		pid = ft_calloc(input->n, sizeof (int));
		while (++i < input->n && pid)
		{
			if (philo->number_eat != -1 && philo->n > 1)
				sem_wait(philo->finished_meal);
			pid[i] = fork();
			if (pid[i] == 0)
				ptread(&philo[i]);
		}
		wait_for_end(philo, input, pid);
	}
}
