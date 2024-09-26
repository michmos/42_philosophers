/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:54:20 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/26 22:23:26 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	**philos;

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
	join_philos(philos);
	cleanup(philos);
	return (0);
}
