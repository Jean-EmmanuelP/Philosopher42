/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrama <jperrama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:30:13 by jperrama          #+#    #+#             */
/*   Updated: 2023/03/06 16:51:34 by jperrama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

/*tte les fonctions pour print les messages de changement d'etat
des philosopher, ave mutex lock et unlock immediatement avant et apres*/

void	ft_mutex_print_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
}

void	ft_mutex_print_think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	ft_mutex_print_fork(t_philo *philo)
{
	print_message(philo, "has taken a fork");
}

void	ft_mutex_print_eating(t_philo *philo)
{
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
}

void	ft_mutex_print_death(t_philo *philo)
{
	print_message(philo, "died");
}
