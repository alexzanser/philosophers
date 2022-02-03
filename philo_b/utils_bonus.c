/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmercy <kmercy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:46:56 by kmercy            #+#    #+#             */
/*   Updated: 2022/01/04 20:32:08 by kmercy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int				i;
	long long int	sign;
	long long int	ans;

	sign = 1;
	i = 0;
	ans = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ans = ans * 10 + (str[i] - '0');
		i++;
	}
	return (ans * sign);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc( size_t number, size_t size )
{
	void	*p;
	size_t	i;

	i = 0;
	p = (void *)malloc(size * number);
	if (!p)
		return (NULL);
	ft_bzero(p, number * size);
	return (p);
}

void	wait_for_end(t_philo *philo, t_input *input, pid_t	*pid)
{
	int			i;

	if (pid[0] != 0)
	{
		if ((philo->n > 1 && !sem_wait(philo->finished_meal)
				&& philo->number_eat != -1) || waitpid(0, 0, 0))
		{
			i = -1;
			while (++i < input->n)
			{
				kill(pid[i], SIGKILL);
			}
		}
	}
}

int	ft_error(void)
{
	printf("Not enough arguments\n");
	return (1);
}
