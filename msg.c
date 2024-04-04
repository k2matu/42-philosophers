/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:14:28 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/04 13:19:30 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(int x, const char *msg)
{
	long	timestamp;

	timestamp = time_in_ms();
	printf("%ld %d %s\n", timestamp, x, msg);
}
