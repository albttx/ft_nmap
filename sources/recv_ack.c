/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_ack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:46:54 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/22 14:58:16 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void		process_return(char buff[], ssize_t size)
{
	struct ip		*iph;
	struct tcphdr	*tcph;
	unsigned short	iplen;

	printf("recv %ld \n", size);
	iph = (struct ip *)buff;
	printf("protocol = %d\n", iph->ip_p);
	if (iph->ip_p == IPPROTO_TCP)
	{
		iplen = iph->ip_hl * 4;
		tcph = (struct tcphdr *)(buff + iplen);
		dbg_print_tcp_types(tcph);
	}
}

void	*recv_ack(void *ptr)
{
	int					sock;
	char				buff[65536];
	struct sockaddr_in	from;
	socklen_t			fromlen;
	ssize_t				recvret;

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if (sock == -1)
	{
		perror("recv sock");
	}
	fromlen = sizeof(from);
	while (42)
	{
		ft_bzero(&from, sizeof(from));
		ft_bzero(buff, sizeof(buff));
		recvret = recvfrom(sock, buff, sizeof(buff), 0, (struct sockaddr *)&from, &fromlen);
		process_return(buff, recvret);
	}
 
	close(sock);
	(void)ptr;
	return (NULL);
}
