/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:57:52 by haouky            #+#    #+#             */
/*   Updated: 2024/08/01 11:21:11 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutexinit(t_table *tbl)
{
	int	i;

	i = 0;
	pthread_mutex_init(&tbl->mprint, NULL);
	pthread_mutex_init(&tbl->mdeath, NULL);
	pthread_mutex_init(&tbl->mfulls, NULL);
	while (i < tbl->nphilo)
	{
		pthread_mutex_init(&tbl->forks[i], NULL);
		i++;
	}
	return (i);
}

void	setidplus(t_table *tbl)
{
	int	i;
	int	n;

	i = 0;
	while (i < tbl->nphilo)
	{
		tbl->philos[i].idphilo = i + 1;
		tbl->philos[i].table = tbl;
		tbl->philos[i].meals = 0;
		tbl->philos[i].shoudeat = tbl->nml;
		tbl->philos[i].ttdie = tbl->ttdie;
		tbl->philos[i].ttsleap = tbl->ttsleap;
		tbl->philos[i].tteat = tbl->tteat;
		tbl->philos[i].left_fork = &tbl->forks[i];
		n = (i + 1) % tbl->nphilo;
		tbl->philos[i].right_fork = &tbl->forks[n];
		i++;
	}
}

int	creat_th(t_table *tbl)
{
	int	i;

	i = 0;
	tbl->sttime = gettime();
	if (tbl->nphilo == 1)
	{
		tbl->philos[i].tlastmel = tbl->sttime;
		pthread_create(&tbl->philos[i].philo, NULL, oneth, &tbl->philos[i]);
	}
	while (tbl->nphilo != 1 && i < tbl->nphilo)
	{
		tbl->philos[i].tlastmel = tbl->sttime;
		pthread_create(&tbl->philos[i].philo, NULL, party, &tbl->philos[i]);
		i++;
	}
	return (i);
}

void	setmutex(pthread_mutex_t *mutx, long *set, long value)
{
	pthread_mutex_lock(mutx);
	if (value == -2)
		*set += 1;
	else
		*set = value;
	pthread_mutex_unlock(mutx);
}

long	getmutex(pthread_mutex_t *mutx, long *see)
{
	long	value;

	pthread_mutex_lock(mutx);
	value = *see;
	pthread_mutex_unlock(mutx);
	return (value);
}
