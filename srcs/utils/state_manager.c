/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrama <jperrama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:30:18 by jperrama          #+#    #+#             */
/*   Updated: 2023/03/06 16:15:08 by jperrama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

/*
** Function that destroys the mutex pointed by forks in reverse order and
** frees the memory allocated for forks, returns -1.
*/
int	mutex_clean(t_table *table, int i)
{
	while (i >= 0)
		pthread_mutex_destroy(&table->forks[i--]);
	if (table->forks)
		free(table->forks);
	return (-1);
}

/*
** Function to free the resources allocated for philosophers and forks.
*/
void	clean(t_table *table)
{
	if (table->philo_list)
		free(table->philo_list);
	if (table->forks)
		free(table->forks);
}
