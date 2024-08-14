/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:51:48 by mmoser            #+#    #+#             */
/*   Updated: 2024/08/12 17:56:27 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_philo **philos)
{
	size_t	i;
	long	start_time;

	i = 0;
	start_time = get_mic_sec_since(0);
	while(philos[i])
	{
		philos[i]->start_time = start_time;
		set_mtx_bool(&philos[i]->start, true);
		i++;
	}
}

void	end_simulation(t_philo **philos)
{
	size_t	i;

	i = 0;
	while(philos[i])
	{
		set_mtx_bool(&philos[i]->terminate, true);
		i++;
	}
}
