/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:21:35 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/18 10:57:20 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	p_strlen(const char *s)
{
	long	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	p_atol(const char *str)
{
	int		i;
	long	n;
	long	negative;

	i = 0;
	n = 0;
	negative = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		negative = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (i != p_strlen(str))
		return (-1);
	return (n * negative);
}
