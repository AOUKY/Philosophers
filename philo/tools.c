/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouky <haouky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:20:50 by haouky            #+#    #+#             */
/*   Updated: 2024/08/03 09:50:55 by haouky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ston(char *s)
{
	long	n;
	int		i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		n = (n * 10) + (s[i] - 48);
		i++;
	}
	return (n);
}

int	freturn(char *s)
{
	printf("%s\n", s);
	return (1);
}

int	fullt(t_table *tbl, int c, char **v)
{
	tbl->nphilo = ston(v[1]);
	tbl->ttdie = ston(v[2]);
	tbl->tteat = ston(v[3]);
	tbl->ttsleap = ston(v[4]);
	if (c == 6)
		tbl->nml = ston(v[5]);
	else
		tbl->nml = -1;
	tbl->death = 0;
	tbl->nfullphilos = 0;
	if (tbl->nphilo == 0 || tbl->ttdie < 60 || tbl->tteat < 60
		|| tbl->ttsleap < 60 || tbl->nml == 0)
		return (1);
	return (0);
}

long	gettime(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	ft_usleep(long timeofsleep, t_philo *philo)
{
	long	st;

	st = 0;
	st = gettime();
	while (1)
	{
		if (chekdeath(philo))
			return (1);
		if ((gettime() - st) > timeofsleep)
		{
			return (0);
		}
		usleep(300);
	}
	return (0);
}
