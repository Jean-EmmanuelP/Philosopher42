#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# define PRINT_MESSAGE(p, format) \
	pthread_mutex_lock(&(p->table->print)); \
	printf("%lld %d " format "\n", runtime(p), p->num); \
	pthread_mutex_unlock(&(p->table->print));

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>

/*
	Cette structure définit les attributs d'un philosophe dans le contexte
	du problème de dîner des philosophes.
*/
typedef struct s_philo
{	
	int				num;
	int				philo_count;
	int				philo_life;
	int				philo_meal;
	int				philo_sleep;
	int				philo_max_meal;
	int				meal_count;
	long long		start_time;
	long long		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	pmutex;
	pthread_mutex_t	*fork_one;
	pthread_mutex_t	*fork_two;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death_auth;
	struct s_table	*table;
}	t_philo;

/*
	Cette structure représente la table à laquelle les philosophes sont assignés,
	elle contient notamment des informations sur leur vie, leur nourriture, leur
	mort et leurs fourchettes, ainsi qu'un moniteur pour surveiller leur état.
*/
typedef struct s_table
{
    long long start_time;
    int philo_count;
    int philo_life;
    int philo_meal;
    int philo_sleep;
    int philo_max_meal;
    int death;
    pthread_mutex_t death_auth;
    pthread_mutex_t* forks;
    pthread_mutex_t print;
    struct s_philo* philo_list;
    pthread_t monitor_id[2];
}	t_table;

/* LIB */
long 			ft_atol(const char *str);
char 			**ft_split(char const *s, char c);
char 			*ft_strdup(const char *s1);
char 			**ft_freetab(char **tab);
unsigned long 	ft_strlen(const char *s);

/* PARSING.C */
int				parameter_table(int argc, char **argv, t_table *table);

/* TIME.C */
long long 		timestamp_ms(void);
long long 		runtime(struct s_philo *philo);
int 			check_last_meal_time(t_philo *philo);
void 			philo_update(t_philo *philo);
void 			action_time(t_philo *philo, int action);

/* THREAD_MONITOR.C */
void 			*ft_starve_monitor(void *ptr);
void 			*ft_meal_monitor(void *ptr);

/* STOP.C */
void 			death_cert(t_table *table);
int 			death_check(t_table *table);
int 			last_meal_check(t_philo *philo);

/* PHILO_LOOP.C */
int 			stop_condition(t_philo *philo);
void 			*ft_start_thread_philo(void *ptr);

/* PHILO_CREATE.C */
int 			create_start_philo(t_table *table);

/* MUTEX_PRINT.C */
void 			ft_mutex_print_sleep(t_philo *philo);
void 			ft_mutex_print_fork(t_philo *philo);
void 			ft_mutex_print_think(t_philo *philo);
void 			ft_mutex_print_eating(t_philo *philo);
void 			ft_mutex_print_death(t_philo *philo);

/* PROBLEM_MANAGER.C */
int 			mutex_clean(t_table *table, int i);
void 			clean(t_table *table);

#endif
