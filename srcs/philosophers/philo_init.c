/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrama <jperrama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:30:22 by jperrama          #+#    #+#             */
/*   Updated: 2023/03/06 15:48:04 by jperrama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

/*
	Cette fonction évite que les philosophes ne prennent pas les mêmes
	fourchettes en même temps,
	évitant ainsi un blocage ou une attente infinie qui empêche les
	philosophes de manger et évite
	que le programme ne tombe en panne.
*/
void	fork_choice(t_table *table, t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->num - 1;
	right_fork = philo->num % table->philo_count;
	if (left_fork < right_fork)
	{
		philo->fork_one = &table->forks[left_fork];
		philo->fork_two = &table->forks[right_fork];
	}
	else
	{
		philo->fork_one = &table->forks[right_fork];
		philo->fork_two = &table->forks[left_fork];
	}
}

// Paramétrage des données pour les philosophes.
void	ft_philo_attributes(t_table *table, int i)
{
	t_philo	*philo;

	philo = &table->philo_list[i];
	philo->num = i + 1;
	philo->meal_count = 0;
	philo->start_time = table->start_time;
	philo->philo_count = table->philo_count;
	philo->philo_life = table->philo_life;
	philo->philo_meal = table->philo_meal;
	philo->philo_sleep = table->philo_sleep;
	philo->philo_max_meal = table->philo_max_meal;
	philo->print = &table->print;
	philo->death_auth = &table->death_auth;
	philo->table = table;
	philo->last_meal = table->start_time;
}

// Cette fonction initialise les mutex pour chaque philosophe
// dans la structure de la table
int	ft_pmutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->philo_list[i].pmutex, 0) != 0)
			break ;
		i++;
	}
	if (i < table->philo_count)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&table->philo_list[i].pmutex);
		return (-1);
	}
	return (1);
}

/* Crée, initialise et lance les threads de chaque philosophe */
int	create_start_philo(t_table *table)
{
	int	i;

	i = -1;
	table->philo_list = malloc(sizeof(t_philo) * (table->philo_count));
	if (table->philo_list == NULL || ft_pmutex(table) == -1)
		return (-1);
	while (++i < table->philo_count)
	{
		ft_philo_attributes(table, i);
		fork_choice(table, &table->philo_list[i]);
		if (pthread_create(&table->philo_list[i].thread_id, NULL,
				ft_start_thread_philo, &table->philo_list[i]))
			return (death_cert(table), i--, -1);
	}
	return (1);
}
