/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:54:56 by haouky            #+#    #+#             */
/*   Updated: 2024/08/04 11:28:27 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*oneth(void *p)
{
	t_philo	*philo;

	philo = p;
	ft_print(philo, "is thinking");
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	while (1)
	{
		if (chekdeath(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
	}
}

int	ft_print(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->table->mprint);
	if (chekdeath(philo))
	{
		pthread_mutex_unlock(&philo->table->mprint);
		return (1);
	}
	printf("%ld %i %s\n", gettime() - philo->table->sttime, philo->idphilo, s);
	pthread_mutex_unlock(&philo->table->mprint);
	return (0);
}
