/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:20:18 by mmoser            #+#    #+#             */
/*   Updated: 2024/08/12 16:20:13 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

static const char	*activity[] = {
	[FORK] = "has taken a fork",
	[EATING] = "is eating",
	[SLEEPING] = "is sleeping",
	[THINKING] = "is thinking",
	[DIED] = "died"
};


void	print_state_change(t_state state, t_philo *philo, long time_stamp)
{
	static t_state			last_state;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	if (last_state == DIED)
	{
		pthread_mutex_unlock(&lock);
		return ;
	}
	last_state = state;
	printf("%li %zu %s\n", time_stamp, philo->idx, activity[state]);
	pthread_mutex_unlock(&lock);
}

void	put_err(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}
