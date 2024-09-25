/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:07:42 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/25 12:33:02 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_mtx_bool(t_mtx_bool	*mtx_bool)
{
	bool	result;

	pthread_mutex_lock(&mtx_bool->lock);
	result = mtx_bool->val;
	pthread_mutex_unlock(&mtx_bool->lock);
	return (result);
}

void	set_mtx_bool(t_mtx_bool	*mtx_bool, bool new_val)
{
	pthread_mutex_lock(&mtx_bool->lock);
	mtx_bool->val = new_val;
	pthread_mutex_unlock(&mtx_bool->lock);
}

t_micsec	get_mtx_time(t_mtx_time *mtx_time)
{
	t_micsec	result;

	pthread_mutex_lock(&mtx_time->lock);
	result = mtx_time->val;
	pthread_mutex_unlock(&mtx_time->lock);
	return (result);
}

void	set_mtx_time(t_mtx_time *mtx_time, t_micsec new_time)
{
	pthread_mutex_lock(&mtx_time->lock);
	mtx_time->val = new_time;
	pthread_mutex_unlock(&mtx_time->lock);
}
