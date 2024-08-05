/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:27:45 by haouky            #+#    #+#             */
/*   Updated: 2024/08/05 09:07:17 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			philo;
	int					idphilo;
	long				tlastmel;
	long				meals;
	long				tteat;
	long				ttdie;
	long				ttsleap;
	long				shoudeat;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	t_table				*table;
}						t_philo; 

typedef struct s_table
{
	long				nphilo;
	long				tteat;
	long				ttdie;
	long				ttsleap;
	long				nml;
	long				sttime;
	long				death;
	long				nfullphilos;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mprint;
	pthread_mutex_t		mdeath;
	pthread_mutex_t		mfulls;

}						t_table;

long					gettime(void);
long					ston(char *s);
int						freturn(char *s);
int						fullt(t_table *tbl, int c, char **v);
int						ft_usleep(long timeofsleep, t_philo *philo);
int						mutexinit(t_table *tbl);
int						creat_th(t_table *tbl);
int						chekdeath(t_philo *philo);
void					setidplus(t_table *tbl);
void					*oneth(void *p);
void					*party(void *p);
int						ft_print(t_philo *philo, char *s);
void					setmutex(pthread_mutex_t *mutx, long *set, long value);
long					getmutex(pthread_mutex_t *mutx, long *see);
#endif