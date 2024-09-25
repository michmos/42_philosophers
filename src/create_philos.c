/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:35:40 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/25 12:43:27 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO: is it correct that we are not initiating the hungry lock?
static int	init_locks(t_philo *philo)
{
	int	s;

	s = pthread_mutex_init(&philo->start.lock, NULL);
	if (s != 0)
	{
		return (-1);
	}
	s = pthread_mutex_init(&philo->terminate.lock, NULL);
	if (s != 0)
	{
		pthread_mutex_destroy(&philo->start.lock);
		return (-1);
	}
	return (0);
}

static t_philo	*create_philo(t_params *params, size_t idx)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		return (NULL);
	}
	*philo = (t_philo) {.idx=idx, .params=params, .start.val=false, .terminate.val=false, .hungry.val = true};
	if (init_locks(philo) == -1)
	{
		free(philo);
		return (NULL);
	}
	if (pthread_create(&philo->tid, NULL, lifecycle, (void *)philo) == -1)
	{
		cleanup_philo(philo);
		return (NULL);
	}
	return (philo);
}

t_philo	**create_philos(t_params *params)
{
	size_t			i;
	t_philo			**philos;

	philos = malloc(sizeof(t_philo *) * (params->num_philos + 1));
	if (!philos)
	{
		return (NULL);
	}

	i = 0;
	while (i < params->num_philos)
	{
		philos[i] = create_philo(params, i);
		if (!philos[i])
		{
			start_simulation(philos);
			join_philos(philos);
			cleanup_philos(philos);
			return (NULL);
		}
		i++;
	}
	philos[i] = NULL;
	return (philos);
}
