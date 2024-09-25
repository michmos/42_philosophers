/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:58:29 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/25 12:44:24 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	starved(t_philo *philo)
{
	return (get_mic_sec_since(philo->start_time) - get_mtx_time(&philo->last_eat_time) >= philo->params->t2d);
}

static void	grab_forks(t_philo *philo)
{
	if (philo->idx % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state_change(FORK, philo, get_mic_sec_since(philo->start_time));
		pthread_mutex_lock(philo->right_fork);
		print_state_change(FORK, philo, get_mic_sec_since(philo->start_time));
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state_change(FORK, philo, get_mic_sec_since(philo->start_time));
		pthread_mutex_lock(philo->left_fork);
		print_state_change(FORK, philo, get_mic_sec_since(philo->start_time));
	}
}

int	eat(t_philo *philo)
{
	t_micsec	eat_time;

	if (philo->params->num_philos == 1)
	{
		wait_mic_sec(philo, philo->params->t2d);
		return (-1);
	}
	grab_forks(philo);
	eat_time = get_mic_sec_since(philo->start_time);
	print_state_change(EATING, philo, eat_time);
	set_mtx_time(&philo->last_eat_time, eat_time);
	philo->times_eaten += 1;
	if (philo->times_eaten == philo->params->eat_requ)
	{
		set_mtx_bool(&philo->hungry, false);
	}
	if (wait_mic_sec(philo, philo->params->t2e) == -1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	// put down forks
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	my_sleep(t_philo *philo)
{
	print_state_change(SLEEPING, philo, get_mic_sec_since(philo->start_time));
	if (wait_mic_sec(philo, philo->params->t2s) == -1)
	{
		return (-1);
	}
	return (0);
}

int	think(t_philo *philo)
{
	print_state_change(THINKING, philo, get_mic_sec_since(philo->start_time));
	return (0);
}
