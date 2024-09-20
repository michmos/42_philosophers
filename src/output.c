/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:20:18 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/20 15:51:08 by mmoser           ###   ########.fr       */
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


// TODO: is last_state a form of communication between philosophers
// in some way the philo knows what the previous philo died - so I guess yes
// maybe it would make more sense to get the time stamp inside the lock - then
// it would at least garantuee that all timestamps are in order
// on the other hand would it not anyore reflect the actual timestamp since 
// you might have been waiting for some time to get inside
void	print_state_change(t_state state, t_philo *philo, t_micsec time_stamp)
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
	printf("%li %zu %s\n", time_stamp/1000, philo->idx, activity[state]);
	pthread_mutex_unlock(&lock);
}

void	put_err(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}
