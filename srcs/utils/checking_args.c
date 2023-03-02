#include "../../include/philosopher.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*verifie les arguments pour s'assurer qu'ils sont valides pour ce programme*/
int	checkarg(char *str)
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
	if (num < 0 || num > INT_MAX)
		return (-1);
	return (1);
}

/*assigne les parametres a la structure table et
renvoi -1 ou 1 suivant si ca a echoue ou reussi*/
int parameter_table(int argc, char **argv, t_table *table)
{
	int i;
	if (argc < 5 || argc > 6)
		return (-1);
	i = 0;
	while (++i < argc)
	{
		if (checkarg(argv[i]) == -1)
			return (-1);
	}
	if (ft_atol(argv[1]) == 0)
		return (-1);
	table->philo_count = ft_atol(argv[1]);
	table->philo_life = ft_atol(argv[2]);
	table->philo_meal = ft_atol(argv[3]);
	table->philo_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		if (ft_atol(argv[5]) == 0)
			return (-1);
		table->philo_max_meal = ft_atol(argv[5]);
	}
	else
		table->philo_max_meal = -1;
	table->death = 0;
	table->start_time = timestamp_ms();
	return (1);
}
