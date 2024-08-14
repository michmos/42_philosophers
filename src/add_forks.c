/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:38:41 by mmoser            #+#    #+#             */
/*   Updated: 2024/08/12 11:34:21 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo **philos, pthread_mutex_t *forks, size_t num_philos)
{
	size_t	i;
	int		s;

	i = 0;
	while (i < num_philos)
	{
		if (i % 2 == 0)
		{
			philos[i]->frst_fork = &forks[i];
			if (num_philos == 1)
				philos[0]->scnd_fork = NULL;
			else if (i == num_philos - 1)
				philos[i]->scnd_fork = &forks[0];
			else
				philos[i]->scnd_fork = &forks[i + 1];
		}
		else
		{
			philos[i]->scnd_fork = &forks[i];
			if (i == num_philos - 1)
				philos[i]->frst_fork = &forks[0];
			else
				philos[i]->frst_fork = &forks[i + 1];
		}
		i++;
	}
}

static int	init_forks(pthread_mutex_t *forks, size_t num)
{
	size_t	i;
	int		s;

	i = 0;
	while (i < num)
	{
		s = pthread_mutex_init(&forks[i], NULL);
		if (s != 0)
		{
			destroy_n_mtxs(forks, i - 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	add_forks(t_philo **philos, size_t num_philos)
{
	pthread_mutex_t	*forks;
	int				s;

	forks = malloc(num_philos * sizeof(pthread_mutex_t));
	if (!forks)
	{
		return (-1);
	}

	if (init_forks(forks, num_philos) != 0)
	{
		free(forks);
		return (-1);
	}
	assign_forks(philos, forks, num_philos);
	return (0);
}
