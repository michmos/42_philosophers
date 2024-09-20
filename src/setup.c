/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:23:24 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/19 11:32:09 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_params	*parse_params(char *argv[])
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	if (!params)
	{
		return (NULL);
	}

	params->num_philos = ft_atoi(argv[1]);
	params->t2d = ft_atoi(argv[2]);
	params->t2e = ft_atoi(argv[3]);
	params->t2s = ft_atoi(argv[4]);
	params->eat_requ = -1;
	if (argv[5])
	{
		params->eat_requ = ft_atoi(argv[5]);
	}
	return (params);

}

int	setup_simulation(char *argv[], t_philo ***philos)
{
	t_params	*params;

	params = parse_params(argv);
	if (!params)
	{
		return (-1);
	}
	*philos = create_philos(params);
	if (!*philos)
	{
		free(params);
		return (-1);
	}
	if (add_forks(*philos, params->num_philos) != 0)
	{
		free(params);
		cleanup_philos(*philos);
		return (-1);
	}
	return (0);
}
