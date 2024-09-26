/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:20:18 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/26 22:21:37 by mmoser           ###   ########.fr       */
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

int	print_state_change(t_state state, t_philo *philo, t_micsec time_stamp)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	static bool	print = true;

	pthread_mutex_lock(&lock);
	if (print == false || (int) state == -1)
	{
		print = false;
		pthread_mutex_unlock(&lock);
		return (-1);
	}
	else if (state == DIED)
	{
		print = false;
	}
	printf("%li %zu %s\n", time_stamp/1000, philo->idx, activity[state]);
	pthread_mutex_unlock(&lock);
	return (0);
}

void	put_err(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}
