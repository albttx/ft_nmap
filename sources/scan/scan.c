/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:30:55 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/24 15:21:11 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void	scan(t_ip *ip, t_list *port_lst)
{
	pthread_t			sniffer_thread;

	if (pthread_create(&sniffer_thread, NULL, listener, (void *)port_lst) < 0)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	if (g_env.type_flags & S_SYN) scan_syn(ip->ipv4name);
	if (g_env.type_flags & S_FIN) scan_ack(ip->ipv4name);
	if (g_env.type_flags & S_ACK) scan_fin(ip->ipv4name);

	if (pthread_join(sniffer_thread, NULL))
	{
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}
	print_port_lst(port_lst);
}
