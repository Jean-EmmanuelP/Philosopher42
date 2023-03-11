/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrama <jperrama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:30:24 by jperrama          #+#    #+#             */
/*   Updated: 2023/03/06 16:49:47 by jperrama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

/*
	Vérifie si le philosophe est mort, 
	sinon libère la fourchette et retourne 1, sinon retourne -1
*/
int	fork_release(struct s_philo *philo, int forks)
{
	if (death_check(philo->table) == -1)
	{
		pthread_mutex_unlock(philo->fork_one);
		if (forks == 2)
			pthread_mutex_unlock(philo->fork_two);
		return (-1);
	}
	return (1);
}

/* 
	Verifie si un philosophe est mort,
	retourne -1 si oui, 1 sinon 
*/
void	philo_eat(t_philo *philo)
{
	if (death_check(philo->table) == -1)
		return ;
	pthread_mutex_lock(philo->fork_one);
	if (fork_release(philo, 1) == -1)
	{
		pthread_mutex_unlock(philo->fork_one);
		return ;
	}
	ft_mutex_print_fork(philo);
	if (philo->philo_count == 1)
	{
		usleep((philo->philo_life + 2) * 1000);
	}
	pthread_mutex_lock(philo->fork_two);
	if (fork_release(philo, 2) == -1)
	{
		pthread_mutex_unlock(philo->fork_one);
		pthread_mutex_unlock(philo->fork_two);
		return ;
	}
	ft_mutex_print_eating(philo);
	philo_update(philo);
	action_time(philo, 1);
	pthread_mutex_unlock(philo->fork_one);
	pthread_mutex_unlock(philo->fork_two);
}

/*
	La fonction philo_sleep 
	permet à un philosophe de dormir pendant un certain temps.
*/
void	philo_sleep(t_philo *philo)
{
	if (death_check(philo->table) == -1)
		return ;
	ft_mutex_print_sleep(philo);
	action_time(philo, 2);
	if (death_check(philo->table) == -1)
		return ;
	ft_mutex_print_think(philo);
	if (philo->philo_count % 2 == 1)
		usleep((philo->philo_meal / 2) * 1000);
}

/*	Cette fonction gère les délais de 
	départ des philosophes pour éviter
	les blocages et les attentes infinies.
*/
void	start_delay(t_philo *philo)
{
	int	delay;

	delay = 0;
	if (philo->philo_count % 2 == 0 && philo->num % 2 == 0)
		delay = 30;
	else if (philo->philo_count % 2 == 1)
	{
		if (philo->num % 3 == 2)
			delay = 30;
		else if (philo->num % 3 == 0)
			delay = 60;
	}
	if (delay > 0)
		usleep(delay * 1000);
}

/*
	Cette fonction exécute le cycle de vie des philosophes en vérifiant
	régulièrement l'état de la table et en appelant les fonctions eat et
	sleep si la mort n'a pas été signalée.
*/
void	*ft_start_thread_philo(void *ptr)
{
	t_philo	*philo;
	int		death;

	philo = (t_philo *)ptr;
	start_delay(philo);
	death = death_check(philo->table);
	while (death == 1)
	{
		if (death_check(philo->table) != 1)
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		death = death_check(philo->table);
	}
	return (NULL);
}
