/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrama <jperrama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:30:00 by jperrama          #+#    #+#             */
/*   Updated: 2023/03/06 16:19:43 by jperrama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*
	Détruit tous les mutex créés pour les philosophes,
	les fourchettes et les moniteurs
	Destruction des mutex pour les philosophes et les fourchettes
	Destruction des mutex pour les moniteurs
*/
void	ft_mutex_destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philo_list[i].pmutex);
		pthread_mutex_destroy(&table->forks[i]);
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->death_auth);
}

/*
	// Attente de la fin des threads pour les philosophes
	// Attente de la fin du thread pour le moniteur de mort
	// Attente de la fin du thread pour le moniteur de repas (si argc == 6)
*/
void	ft_thread_join(t_table *table, int argc)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		pthread_join(table->philo_list[i].thread_id, NULL);
	pthread_join(table->monitor_id[0], NULL);
	if (argc == 6)
		pthread_join(table->monitor_id[1], NULL);
}

/*
	// Création des threads pour les philosophes
	// Création du thread pour le moniteur de mort
	// Création du thread pour le moniteur de repas (si argc == 6)
*/
int	ft_thread_create(t_table *table, int argc)
{
	int	ret;

	ret = create_start_philo(table);
	if (ret == -1)
		return (-1);
	ret = pthread_create(&table->monitor_id[0], NULL, ft_starve_monitor, table);
	if (ret != 0)
		return (-1);
	if (argc == 6)
	{
		ret = pthread_create(&table->monitor_id[1], NULL, ft_meal_monitor,
				table);
		if (ret != 0)
			return (-1);
	}
	return (1);
}

/*initialisation de tout les mutex necessaires pour le projet :
un par fork, 
un par philosopher(pour le time since last meal, et le compte de repas),
un pour print
et un pour signaler une condition d'arret(death)*/
int	ft_mutex_init(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (table->forks == NULL)
		return (-1);
	i = -1;
	while (++i < table->philo_count)
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (mutex_clean(table, i));
	if (pthread_mutex_init(&table->death_auth, NULL))
		return (mutex_clean(table, i - 1));
	if (pthread_mutex_init(&table->print, NULL))
	{
		mutex_clean(table, i);
		pthread_mutex_destroy(&table->death_auth);
		return (-1);
	}
	return (1);
}

/*fonction main
verifie les arguments et les assignent a la structure principale (table)
initialise les mutex
cree les threads
attends leurs resolution
detruit les mutex
et detruit les donnees sur la heap avant de cloturer le programme*/
int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	thread;

	if (ft_atol(argv[1]) == 1)
	{
		if (pthread_create(&thread, NULL, thread_for_one, NULL) != 0)
			return (-1);
		printf("0 1 has taken a fork\n");
		pthread_detach(thread);
		return (0);
	}
	if (parameter_table(argc, argv, &table) == -1)
		return (0);
	if (ft_mutex_init(&table) == -1)
		return (0);
	if (ft_thread_create(&table, argc) == -1)
		death_cert(&table);
	ft_thread_join(&table, argc);
	ft_mutex_destroy(&table);
	clean(&table);
	return (0);
}
