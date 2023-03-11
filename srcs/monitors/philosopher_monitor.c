/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrama <jperrama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:30:29 by jperrama          #+#    #+#             */
/*   Updated: 2023/03/06 15:42:16 by jperrama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

/* Vérifie régulièrement si un philosophe est mort de faim */
void	*ft_starve_monitor(void *ptr)
{
	t_table	*table;
	int		i;

	table = (t_table *)ptr;
	while (death_check(table) == 1)
	{
		i = 0;
		while (i < table->philo_count)
		{
			if (death_check(table) == -1)
				return (NULL);
			if (check_last_meal_time(&table->philo_list[i]) == -1)
			{
				ft_mutex_print_death(&table->philo_list[i]);
				death_cert(table);
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

/*
	Vérifie régulièrement si tous les philosophes
	ont mangé un nombre suffisant de repas
*/
void	*ft_meal_monitor(void *ptr)
{
	t_table	*table;
	int		x;

	table = (t_table *)ptr;
	x = 0;
	while (x < table->philo_count && death_check(table) == 1)
	{
		while (x < table->philo_count)
		{
			if (death_check(table) == -1)
				return (NULL);
			if (table->philo_max_meal != -1 && table->philo_list[x].meal_count
				< table->philo_max_meal)
				break ;
			x++;
		}
		if (x == table->philo_count)
			break ;
		usleep(1000);
	}
	if (death_check(table) == -1)
		return (NULL);
	death_cert(table);
	return (NULL);
}
