#include "../../include/philosopher.h"

/*
	Fonction qui détruit les mutex pointés par forks dans
	l'ordre inverse et libère la mémoire allouée pour forks, retourne -1.
*/
int mutex_clean(t_table *table, int i)
{
    while (i >= 0)
    {
        pthread_mutex_destroy(&table->forks[i--]);
    }
    return table->forks ? (free(table->forks), -1) : -1;
}

/* 	Fonction pour
	libérer les ressources allouées pour les philosophes et les fourchettes.
*/
void clean(t_table *table)
{
    table->philo_list ? free(table->philo_list) : 0;
    table->forks ? free(table->forks) : 0;
}
