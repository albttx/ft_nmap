/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_udp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:22:03 by ale-batt          #+#    #+#             */
/*   Updated: 2017/08/05 11:57:14 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

/*
 *  -= UDP SCAN =-
 *
 *  Send ACK
 *  Wait for :
 *  	OPEN         no response
 *  	FILTERED     impossible (no response)
 *  	CLOSE        ICMP port unreachable
*/

int		udp_default(void)
{
	return (OPEN);
}

int		udp_set(enum e_tcp_type types)
{
	return (udp_default());
}

void	scan_udp(char *ipv4name)
{
	int					i;
	int					ret;
	int					sock;
	struct sockaddr_in	sin;

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock <= 0)
	{
		perror("UDP socket");
		exit(EXIT_FAILURE);
	}
	ft_bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ipv4name);
	i = g_env.port[0];
	while (i < g_env.port[1])
	{
		sin.sin_port = htons(i);
		ret = sendto(sock, "42", 2, 0, (struct sockaddr *)&sin, sizeof(sin));
		if (ret <= 0)
			perror("udp sendto()");
		i++;
	}
}
