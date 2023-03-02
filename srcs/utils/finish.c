#include "../../include/philosopher.h"

/*
	Verrouille l'accès à la variable
	'death' de la table et la met à 1 pour indiquer la fin du programme.
*/
void death_cert(t_table *table)
{
    pthread_mutex_lock(&table->death_auth);
    table->death = 1;
    pthread_mutex_unlock(&table->death_auth);
}

/*
	Vérifie si le programme doit se terminer
	en vérifiant si le flag de mort est activé dans la structure de la table.
*/
int	death_check(t_table *table)
{
	int	ret;

	pthread_mutex_lock(&table->death_auth);
	ret = table->death == 1 ? -1 : 1;
	pthread_mutex_unlock(&table->death_auth);

	return (ret);
}

/*
	Vérifie si le philosophe a atteint le nombre maximum de repas
	autorisés en utilisant une mutex pour accéder aux variables partagées
	en toute sécurité.
*/
int	last_meal_check(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->pmutex);
	res = (philo->meal_count >= philo->philo_max_meal);
	pthread_mutex_unlock(&philo->pmutex);
	return (res);
}
