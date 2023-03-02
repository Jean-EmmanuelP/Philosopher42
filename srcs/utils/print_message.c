#include "../../include/philosopher.h"

/*tte les fonctions pour print les messages de changement d'etat
des philosopher, ave mutex lock et unlock immediatement avant et apres*/

void ft_mutex_print_sleep(t_philo *philo) {
	PRINT_MESSAGE(philo, "is sleeping");
}

void ft_mutex_print_think(t_philo *philo) {
	PRINT_MESSAGE(philo, "is thinking");
}

void ft_mutex_print_fork(t_philo *philo) {
	PRINT_MESSAGE(philo, "has taken a fork");
}

void ft_mutex_print_eating(t_philo *philo) {
	PRINT_MESSAGE(philo, "has taken a fork");
	PRINT_MESSAGE(philo, "is eating");
}

void ft_mutex_print_death(t_philo *philo) {
	PRINT_MESSAGE(philo, "died");
}
