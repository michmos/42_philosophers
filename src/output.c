/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:20:18 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/23 18:06:26 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*activity[] = {
	[FORK] = "has taken a fork",
	[EATING] = "is eating",
	[SLEEPING] = "is sleeping",
	[THINKING] = "is thinking",
	[DIED] = "died"
};

// TODO: check whether new version is still working
// theoeretically it is possible that somebody printed that they died but that the monitoring 
// thread was not yet able to set all threads to terminate - so that another tread could still
// print messages
// alternative would be to have a static lock bool
void	print_state_change(t_state state, t_philo *philo, t_micsec time_stamp)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	if (check_mtx_bool(&philo->terminate))
	{
		pthread_mutex_unlock(&lock);
		return ;
	}
	printf("%li %zu %s\n", time_stamp/1000, philo->idx, activity[state]);
	pthread_mutex_unlock(&lock);
}

void	put_err(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}
