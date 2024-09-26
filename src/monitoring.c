/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:03:05 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/26 22:21:59 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	starved(t_philo *philo)
{
	return (get_mic_sec_since(philo->start_time) - philo->last_eat_time >= philo->params->t2d);
}

void	monitor_philos(t_philo **philos)
{
	size_t	i;
	bool	found_hungry_philo;
	
	// find dead philo or all philos full
	while (true)
	{
		i = 0;
		found_hungry_philo = false;
		while (philos[i])
		{
			// check dead
			pthread_mutex_lock(&philos[i]->eat_lock);
			if (starved(philos[i]))
			{
				print_state_change(DIED, philos[i], get_mic_sec_since(philos[i]->start_time));
				pthread_mutex_unlock(&philos[i]->eat_lock);
				return;
			}
			pthread_mutex_unlock(&philos[i]->eat_lock);
			// check stuffed
			if (check_mtx_bool(&philos[i]->hungry))
			{
				found_hungry_philo = true;
			}
			i++;
		}

		if (!found_hungry_philo)
		{
			print_state_change(-1, NULL, 0);
			return ;
		}
	}
}
