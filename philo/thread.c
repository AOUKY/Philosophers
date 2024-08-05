/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:41:34 by haouky            #+#    #+#             */
/*   Updated: 2024/08/04 11:32:38 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chekdeath(t_philo *philo)
{
	if (getmutex(&philo->table->mdeath, &philo->table->death))
		return (1);
	if (gettime() - philo->tlastmel >= philo->ttdie)
	{
		setmutex(&philo->table->mdeath, &philo->table->death, philo->idphilo);
		return (1);
	}
	return (0);
}

static int	se_eating(t_philo *philo)
{
	if (ft_usleep(philo->tteat, philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	philo->tlastmel = gettime();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->meals++;
	return (0);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (ft_print(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	if (ft_print(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (ft_print(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (se_eating(philo));
}

int	ft_sleeping(t_philo *philo, long tsleap)
{
	if (ft_print(philo, "is sleeping"))
		return (1);
	if (ft_usleep(tsleap, philo))
		return (1);
	return (0);
}

void	*party(void *p)
{
	t_philo	*philo;

	philo = p;
	if (philo->idphilo % 2 == 0)
		if (ft_sleeping(philo, philo->ttsleap))
			return (0);
	while (1)
	{
		if (ft_print(philo, "is thinking"))
			return (0);
		if (eating(philo))
		{
			return (0);
		}
		if (philo->shoudeat != -1 && philo->meals == philo->shoudeat)
			setmutex(&philo->table->mfulls, &philo->table->nfullphilos, -2);
		if (ft_sleeping(philo, philo->ttsleap))
		{
			return (0);
		}
	}
	return (0);
}
