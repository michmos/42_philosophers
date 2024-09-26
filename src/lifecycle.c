/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:07:19 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/26 22:30:39 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lifecycle(void *arg)
{
	t_philo	*me;
	static int (*activities[])(t_philo *) = {
		[EATING] = &eat,
		[SLEEPING] = &my_sleep,
		[THINKING] = &think,
	};
	t_state	state;

	me = (t_philo *) arg;

	while (! check_mtx_bool(&me->start))
		usleep(100);

	// divide into groups
	if (me->idx % 2 != 0)
	{
		wait_mic_sec(me->params->t2e / 2);
	}

	// lifecycle
	state = EATING;
	while (true)
	{
		if (activities[state](me) == -1)
		{
			break ;
		}
		state = (state == THINKING) ? EATING : state + 1;
	}
	return (NULL);
}
