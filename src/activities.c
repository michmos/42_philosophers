/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:58:29 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/20 11:25:12 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// TODO: check again what I did wrong here before
static int	wait_mic_sec(t_philo *philo, long	duration, long start_time)
{
	while (get_mic_sec_since(start_time) < duration)
	{
		usleep( USLEEP_TIME);
		if (starved(philo))
		{
			return (-1);
		}
	}
	return (0);
}

int	eat(t_philo *philo)
{
	// grab forks
	pthread_mutex_lock(philo->frst_fork);
	print_state_change(FORK, philo, get_mic_sec_since(philo->start_time)/1000);
	if (!philo->scnd_fork)
	{
		pthread_mutex_unlock(philo->frst_fork);
		wait_mic_sec(philo, philo->params->t2d * 1000, get_mic_sec_since(0));
		set_mtx_bool(&philo->dead, true);
		return (-1);
	}
	pthread_mutex_lock(philo->scnd_fork);
	print_state_change(FORK, philo, get_mic_sec_since(philo->start_time)/1000);

	// eat
	print_state_change(EATING, philo, get_mic_sec_since(philo->start_time)/1000);
	philo->last_eat_time = get_mic_sec_since(philo->start_time);
	philo->times_eaten += 1;
	if (philo->times_eaten == philo->params->eat_requ)
	{
		set_mtx_bool(&philo->hungry, false);
	}
	if (wait_mic_sec(philo, philo->params->t2e * 1000, get_mic_sec_since(0)) == -1)
	{
		set_mtx_bool(&philo->dead, true);
		pthread_mutex_unlock(philo->scnd_fork);
		pthread_mutex_unlock(philo->frst_fork);
		return (-1);
	}

	// put down forks
	pthread_mutex_unlock(philo->scnd_fork);
	pthread_mutex_unlock(philo->frst_fork);
	return (0);
}

int	my_sleep(t_philo *philo)
{
	print_state_change(SLEEPING, philo, get_mic_sec_since(philo->start_time)/1000);
	if (wait_mic_sec(philo, philo->params->t2s * 1000, get_mic_sec_since(0)) == -1)
	{
		set_mtx_bool(&philo->dead, true);
		return (-1);
	}
	return (0);
}

int	think(t_philo *philo)
{
	print_state_change(THINKING, philo, get_mic_sec_since(philo->start_time)/1000);
	return (0);
}

void	die(t_philo *philo)
{
	print_state_change(DIED, philo, get_mic_sec_since(philo->start_time)/1000);
}
