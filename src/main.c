/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:54:20 by mmoser            #+#    #+#             */
/*   Updated: 2024/08/12 17:56:40 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	starved(t_philo *philo)
{
	return (get_mic_sec_since(philo->start_time) - philo->last_eat_time >= philo->params->t2d * 1000);
}

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
	// start
	while (! get_mtx_bool(&me->start))
		;

	// lifecycle
	state = EATING;
	while (! get_mtx_bool(&me->terminate))
	{
		if (starved(me))
		{
			set_mtx_bool(&me->dead, true);
			break;
		}
		if (activities[state](me) == -1)
		{
			break ;
		}
		state = (state == THINKING) ? EATING : state + 1;
	}
	return (NULL);
}

void	monitor_philos(t_philo **philos)
{
	size_t	i;
	
	i = 0;
	// find dead philo
	while (!get_mtx_bool(&philos[i]->dead))
	{
		i++;
		if (i == (*philos)->params->num_philos)
			i = 0;
	}
	print_state_change(DIED, philos[i], get_mic_sec_since(philos[i]->start_time)/1000);
}

int	main(int argc, char *argv[])
{
	t_philo			**philos;

	if ((argc != 5 && argc != 6) || has_syntax_errs(argv))
	{
		put_err(USAGE);
		return (EXIT_FAILURE);
	}
	setup_simulation(argv, &philos);
	start_simulation(philos);
	monitor_philos(philos);
	end_simulation(philos);
	join_philos(philos);
	cleanup_forks(philos);
	cleanup_philos(philos);
	return (0);
}
