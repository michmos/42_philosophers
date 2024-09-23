/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:30:46 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/23 16:34:03 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	has_syntax_err(char *argv[])
{
	size_t	i;
	size_t	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

void	join_philos(t_philo **philos)
{
	size_t	i;
	int		s;

	i = 0;
	while (philos[i])
	{
		s = pthread_join(philos[i]->tid, NULL);
		if (s != 0)
		{
			put_err("thread could not be joined\n");
		}
		i++;
	}
}

int	ft_atoi(const char *nptr)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	sign = 1;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	num = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num *= 10;
		num += nptr[i] - '0';
		i++;
	}
	return ((int) num * sign);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count])
	{
		count++;
	}
	return (count);
}

t_micsec	get_mic_sec_since(t_micsec start_time)
{
	struct timeval timeval;
	t_micsec	time_in_micro;

	if (gettimeofday(&timeval, NULL) == -1)
		return (-1);
	time_in_micro = timeval.tv_usec + 1000000 * timeval.tv_sec - start_time;
	return (time_in_micro);
}

