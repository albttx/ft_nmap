/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:30:55 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/22 19:36:12 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void	create_thread(pthread_t *thread)
{
	char		*msg = "Thread 1";

	if (pthread_create(thread, NULL, recv_ack, (void*)msg) < 0)
	{
		perror("thread ");
		exit(EXIT_FAILURE);
	}
}

void	scan(t_ip *ip)
{
	pthread_t			sniffer_thread;

	create_thread(&sniffer_thread);

	scan_syn(ip->ipv4name);
	puts("scan_syn DONE");

	pthread_join(sniffer_thread, NULL);
}
