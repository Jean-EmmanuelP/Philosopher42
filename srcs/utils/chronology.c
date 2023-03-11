/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronology.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrama <jperrama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:30:08 by jperrama          #+#    #+#             */
/*   Updated: 2023/03/06 16:04:39 by jperrama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

/*
**	Met à jour le temps de la dernière fois que le philosophe a mangé et le
**	nombre de repas,
**	en utilisant le timestamp en millisecondes.
*/

void	philo_update(t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->pmutex);
	now = timestamp_ms();
	philo->meal_count++;
	philo->last_meal = now;
	pthread_mutex_unlock(&philo->pmutex);
}

/*
**	Vérifie si le philosophe a dépassé la durée de vie.
*/

int	check_last_meal_time(t_philo *philo)
{
	long long	last_meal;

	pthread_mutex_lock(philo->fork_one);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->fork_one);
	if (timestamp_ms() - last_meal >= philo->philo_life)
		return (-1);
	return (1);
}

/*
**	Cette fonction retourne le temps actuel en millisecondes.
*/

long long	timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
**	Cette fonction calcule le temps d'exécution depuis le début de la simulation.
*/

long long	runtime(t_philo *philo)
{
	return (timestamp_ms() - philo->start_time);
}

/*
**	Cette fonction permet de gérer le temps d'action d'un philosophe en attendant
**	que le temps écoulé soit égal à la durée de l'action.
**	Si un philosophe meurt pendant l'attente, la fonction s'arrête immédiatement.
*/

void	action_time(t_philo *philo, int action)
{
	long long	start;
	long long	task;

	start = timestamp_ms();
	if (action == 1)
		task = philo->philo_meal;
	else
		task = philo->philo_sleep;
	while (death_check(philo->table) != -1 && timestamp_ms() - start < task)
	{
		usleep(500);
	}
}
