/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:54:20 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/20 15:40:01 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	starved(t_philo *philo)
{
	return (get_mic_sec_since(philo->start_time) - philo->last_eat_time >= philo->params->t2d);
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
	while (! check_mtx_bool(&me->start))
		;

	// lifecycle
	state = EATING;
	while (! check_mtx_bool(&me->terminate) && me->times_eaten < me->params->eat_requ)
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
	bool	found_hungry_philo;
	
	i = 0;
	// find dead philo or all philos full
	while (true)
	{
		i = 0;
		found_hungry_philo = false;
		while (philos[i])
		{
			if (check_mtx_bool(&philos[i]->dead))
			{
				print_state_change(DIED, philos[i], get_mic_sec_since(philos[i]->start_time)/1000);
				return;
			}
			else if (check_mtx_bool(&philos[i]->hungry))
			{
				found_hungry_philo = true;
			}
			i++;
		}

		if (!found_hungry_philo)
			return ;
	}
}

int	main(int argc, char *argv[])
{
	t_philo			**philos;

	if ((argc != 5 && argc != 6) || has_syntax_err(argv))
	{
		put_err(USAGE);
		return (EXIT_FAILURE);
	}
	if (setup_simulation(argv, &philos) == -1)
	{
		put_err("Error occurred during setup\n");
		return (EXIT_FAILURE);
	}
	start_simulation(philos);
	monitor_philos(philos);
	end_simulation(philos);
	join_philos(philos);
	cleanup(philos);
	return (0);
}
