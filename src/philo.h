/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:52:32 by mmoser            #+#    #+#             */
/*   Updated: 2024/08/14 12:42:47 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define USAGE "Please provide the following arguments:\n1. Number of philosophers\n2. Time to die in milisec\n3. Time to eat in milisec\n4. Time to sleep in milisec\n(5. Number of times a philo must eat)\n"
# define USLEEP_TIME 1000

typedef struct s_params
{
	size_t	num_philos;
	size_t	t2d;
	size_t	t2e;
	size_t	t2s;
	size_t	eat_requ;
} t_params;

typedef struct	s_mtx_bool
{
	pthread_mutex_t	lock;
	bool			val;
} t_mtx_bool;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FORK
} t_state;

typedef struct s_philo
{
	t_mtx_bool		dead;
	t_mtx_bool		start;
	t_mtx_bool		terminate;
	t_mtx_bool		hungry;

	size_t			idx;
	pthread_t		tid;
	long			last_eat_time;
	int				times_eaten;
	long			start_time;
	pthread_mutex_t *frst_fork;
	pthread_mutex_t	*scnd_fork;
	const t_params	*params;
} t_philo;

void	*lifecycle(void *arg);
bool	starved(t_philo *philo);

// utils.c ------------------------------------------------------------------ //
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *str);
long	get_mic_sec_since(long start_time);
bool	has_syntax_errs(char *argv[]);
void	join_philos(t_philo **philos);

// output.c ----------------------------------------------------------------- //
void	print_state_change(t_state state, t_philo *philo, long time_stamp);
void	put_err(const char *msg);

// free.c ------------------------------------------------------------------- //
void	sfree(void **ptr);
int		destroy_n_mtxs(pthread_mutex_t *mtxs, size_t len);
void	cleanup_philo(t_philo *philo);
void	cleanup_philos(t_philo **philos);
void	cleanup_forks(t_philo **philos);

// setup.c ------------------------------------------------------------------ //
int	setup_simulation(char *argv[], t_philo ***philos);

// create_philos.c ---------------------------------------------------------- //
t_philo	**create_philos(t_params *params);

// add_forks.c -------------------------------------------------------------- //
int	add_forks(t_philo **philos, size_t num_philos);

// activities.c ------------------------------------------------------------- //
int	eat(t_philo *philo);
int	my_sleep(t_philo *philo);
int	think(t_philo *philo);
void	die(t_philo *philo);

// get_set.c ---------------------------------------------------------------- //
void	start_simulation(t_philo **philos);
void	end_simulation(t_philo **philos);

// get_set.c ---------------------------------------------------------------- //
bool	get_mtx_bool(t_mtx_bool	*mtx_bool);
void	set_mtx_bool(t_mtx_bool	*mtx_bool, bool new_val);

#endif
