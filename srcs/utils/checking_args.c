/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrama <jperrama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:30:05 by jperrama          #+#    #+#             */
/*   Updated: 2023/03/06 16:50:49 by jperrama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_verification(int num, int i)
{
	if ((i == 3 || i == 4 || i == 2) && num < 60)
		return (-1);
	if (i == 1 && num == 0)
		return (-1);
	return (0);
}

/*verifie les arguments pour s'assurer qu'ils sont valides pour ce programme*/
int	checkarg(char *str, int argv)
{
	long	num;
	int		len;
	int		i;

	if (!str || !*str)
		return (-1);
	if (*str == '-')
		str++;
	len = ft_strlen(str);
	if (len == 0 || len > 10)
		return (-1);
	i = 0;
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	num = ft_atol(str);
	if (ft_verification(num, argv) == -1)
		return (-1);
	return (1);
}

/*assigne les parametres a la structure table et
renvoi -1 ou 1 suivant si ca a echoue ou reussi*/
int	parameter_table(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (-1);
	if (!ft_atol(argv[1]) || checkarg(argv[2], 2) == -1
		|| checkarg(argv[3], 3) == -1 || checkarg(argv[4], 4) == -1
		|| (argc == 6 && !ft_atol(argv[5])))
		return (-1);
	table->philo_count = ft_atol(argv[1]);
	table->philo_life = ft_atol(argv[2]);
	table->philo_meal = ft_atol(argv[3]);
	table->philo_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->philo_max_meal = ft_atol(argv[5]);
	else
		table->philo_max_meal = -1;
	table->death = 0;
	table->start_time = timestamp_ms();
	return (1);
}
