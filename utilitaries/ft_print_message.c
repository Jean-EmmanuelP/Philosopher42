/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrama <jperrama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:43:56 by jperrama          #+#    #+#             */
/*   Updated: 2023/03/06 16:44:25 by jperrama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	print_message(t_philo *p, const char *format)
{
	pthread_mutex_lock(&(p->table->print));
	printf("%lld %d %s\n", runtime(p), p->num, format);
	pthread_mutex_unlock(&(p->table->print));
}
