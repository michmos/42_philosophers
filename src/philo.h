/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:52:32 by mmoser            #+#    #+#             */
/*   Updated: 2024/09/25 12:46:16 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define USAGE "Please provide the following arguments:\n1. Number of philosophers\n2. Time to die in milisec\n3. Time to eat in milisec\n4. Time to sleep in milisec\n(5. Number of times a philo must eat)\n"
# define USLEEP_TIME 500

typedef long t_micsec;

typedef struct s_params
{
	size_t		num_philos;
	t_micsec	t2d;
	t_micsec	t2e;
	t_micsec	t2s;
	size_t		eat_requ;
} t_params;

typedef struct	s_mtx_bool
{
	pthread_mutex_t	lock;
	bool			val;
} t_mtx_bool;

typedef struct	s_mtx_time
{
	pthread_mutex_t	lock;
	t_micsec		val;
} t_mtx_time;

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
	t_mtx_bool		start;
	t_mtx_bool		terminate;
	t_mtx_bool		hungry; // TODO: should be renamed - they can still get hungry after they've eaten enough times

	size_t			idx;
	pthread_t		tid;
	t_mtx_time		last_eat_time;	// timestamp of last meal since start in micro sec
	size_t			times_eaten;
	t_micsec		start_time;		// timestamp of start in micro sec
	pthread_mutex_t *left_fork;
	pthread_mutex_t	*right_fork;
	const t_params	*params;
} t_philo;

void		*lifecycle(void *arg);
bool		starved(t_philo *philo);

// utils.c ------------------------------------------------------------------ //
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *str);
t_micsec	get_mic_sec_since(t_micsec start_time);
bool		has_syntax_err(char *argv[]);
void		join_philos(t_philo **philos);
int			wait_mic_sec(t_philo *philo, t_micsec	duration);

// output.c ----------------------------------------------------------------- //
void	print_state_change(t_state state, t_philo *philo, t_micsec time_stamp);
void	put_err(const char *msg);

// free.c ------------------------------------------------------------------- //
void	sfree(void **ptr);
int		destroy_n_mtxs(pthread_mutex_t *mtxs, size_t n);
void	cleanup_philo(t_philo *philo);
void	cleanup_philos(t_philo **philos);
void	cleanup_forks(t_philo **philos);
void	cleanup(t_philo **philos);

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
bool		check_mtx_bool(t_mtx_bool	*mtx_bool);
void		set_mtx_bool(t_mtx_bool	*mtx_bool, bool new_val);
t_micsec	get_mtx_time(t_mtx_time *mtx_time);
void		set_mtx_time(t_mtx_time *mtx_time, t_micsec new_time);

#endif
