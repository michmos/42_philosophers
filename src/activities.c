/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:58:29 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/26 22:30:53 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	eat(t_philo *philo)
{
	t_micsec	eat_time;

	if (philo->params->num_philos == 1)
	{
		wait_mic_sec(philo->params->t2d);
		return (-1);
	}
	grab_forks(philo);
	pthread_mutex_lock(&philo->eat_lock);
	eat_time = get_mic_sec_since(philo->start_time);
	philo->last_eat_time = eat_time;
	if (print_state_change(EATING, philo, eat_time) == -1)
	{
		drop_forks(philo);
		pthread_mutex_unlock(&philo->eat_lock);
		return (-1);
	}
	pthread_mutex_unlock(&philo->eat_lock);
	philo->times_eaten += 1;
	if (philo->times_eaten == philo->params->eat_requ)
	{
		set_mtx_bool(&philo->hungry, false);
	}
	wait_mic_sec(philo->params->t2e);
	// put down forks
	drop_forks(philo);
	return (0);
}

int	my_sleep(t_philo *philo)
{
	if (print_state_change(SLEEPING, philo, get_mic_sec_since(philo->start_time)) == -1)
	{
		return (-1);
	}
	wait_mic_sec(philo->params->t2s);
	return (0);
}

int	think(t_philo *philo)
{
	int	t2t;

	if (print_state_change(THINKING, philo, get_mic_sec_since(philo->start_time)) == -1)
	{
		return (-1);
	}
	if (philo->params->num_philos % 2 != 0)
	{
		t2t = philo->params->t2e * 2 - philo->params->t2s;
		t2t = (t2t > 0) ? t2t : 0;
		wait_mic_sec(t2t);
	}
	return (0);
}
