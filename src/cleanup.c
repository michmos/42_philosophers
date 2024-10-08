/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:30:04 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/26 22:58:44 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	cleanup_philo(t_philo *philo)
{
	if (!philo)
	{
		return;
	}
	pthread_mutex_destroy(&philo->start.lock);
	pthread_mutex_destroy(&philo->hungry.lock);
	pthread_mutex_destroy(&philo->eat_lock);
	free(philo);
}

void	cleanup_philos(t_philo **philos)
{
	size_t	i;

	i = 0;
	while(philos[i])
	{
		cleanup_philo(philos[i]);
		i++;
	}
	free(philos);
}

void	sfree(void **ptr)
{
	if (!ptr || !*ptr)
		return ;

	free(*ptr);
	*ptr = NULL;
}

int	destroy_n_mtxs(pthread_mutex_t *mtxs, size_t n)
{
	size_t	i;
	size_t	s;

	i = 0;
	while (i < n)
	{
		s = pthread_mutex_destroy(&mtxs[i]);
		if (s != 0)
		{
			put_err("mutex destroy failed\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	cleanup_forks(t_philo **philos)
{
	pthread_mutex_t	*forks;

	forks = (*philos)->left_fork;
	destroy_n_mtxs(forks, (*philos)->params->num_philos);
	free(forks);
}

void	cleanup(t_philo **philos)
{
	cleanup_forks(philos);
	free((void *) (*philos)->params);
	cleanup_philos(philos);
}
