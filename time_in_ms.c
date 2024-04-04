/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_in_ms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:36:46 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/03 12:36:59 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	time_in_ms(void)
{
	struct timeval	te;
	long			millisec;

	gettimeofday(&te, NULL);
	millisec = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (millisec);
}
