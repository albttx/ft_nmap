/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:30:55 by ale-batt          #+#    #+#             */
/*   Updated: 2017/08/02 17:20:35 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void	scan(t_ip *ip)
{
	pthread_t	sniffer_thread;
	int			t;

	if (pthread_create(&sniffer_thread, NULL, listener, NULL) < 0)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	/*sleep(1);*/

	puts("START SCAN");
	if (g_env.type_flags & S_SYN) scan_syn(ip->ipv4name);
	if (g_env.type_flags & S_FIN) scan_ack(ip->ipv4name);
	if (g_env.type_flags & S_ACK) scan_fin(ip->ipv4name);
	if (g_env.type_flags & S_NUL) scan_null(ip->ipv4name);
	if (g_env.type_flags & S_XMAS) scan_xmas(ip->ipv4name);

	if (pthread_join(sniffer_thread, NULL))
	{
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}
	print_port_lst(g_env.port_lst);
}
