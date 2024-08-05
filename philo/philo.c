/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:52:44 by haouky            #+#    #+#             */
/*   Updated: 2024/08/04 11:19:58 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thmain(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nphilo)
	{
		pthread_join(table->philos[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < table->nphilo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->mdeath);
	pthread_mutex_destroy(&table->mfulls);
	pthread_mutex_destroy(&table->mprint);
	free(table->philos);
	free(table->forks);
	return (0);
}

static int	semain(t_table *table)
{
	int	i;
	int	n;

	i = 0;
	while (1)
	{
		if (getmutex(&table->mfulls, &table->nfullphilos) == table->nphilo)
		{
			setmutex(&table->mdeath, &table->death, 1);
			break ;
		}
		n = getmutex(&table->mdeath, &table->death);
		if (n)
		{
			pthread_mutex_lock(&table->mprint);
			printf("%ld %i died\n", gettime() - table->sttime, n);
			pthread_mutex_unlock(&table->mprint);
			break ;
		}
	}
	return (thmain(table));
}

int	main(int c, char **v)
{
	t_table			tbl;
	pthread_mutex_t	*fork;
	t_philo			*philo;

	if (c != 5 && c != 6)
	{
		printf("the input shoud be like this:\n");
		return (freturn("./philo nphilos ttdie tteat ttsleap [n_of_meals]"));
	}
	if (fullt(&tbl, c, v))
		return (freturn("error in aregements"));
	fork = malloc(sizeof(pthread_mutex_t) * (tbl.nphilo));
	if (!fork)
		return (freturn("problem in malloc"));
	philo = malloc(sizeof(pthread_t) * (tbl.nphilo));
	if (!philo)
		return (freturn("problem in malloc"));
	tbl.philos = philo;
	tbl.forks = fork;
	mutexinit(&tbl);
	setidplus(&tbl);
	creat_th(&tbl);
	semain(&tbl);
	return (0);
}
