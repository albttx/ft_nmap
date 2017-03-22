/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_ack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:46:54 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/22 19:55:06 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void		process_return(char buff[], ssize_t size)
{
	struct ip			*iph;
	unsigned short		iplen;
	struct tcphdr		*tcph;
	struct sockaddr_in	src;
	struct sockaddr_in	dst;

	printf("recv %ld ", size);
	iph = (struct ip *)buff;
	if (iph->ip_p == IPPROTO_TCP)
	{
		iplen = iph->ip_hl * 4;
		tcph = (struct tcphdr *)(buff + iplen);
		ft_bzero(&src, sizeof(src));
		ft_bzero(&dst, sizeof(dst));
		src.sin_addr = iph->ip_src;
		dst.sin_addr = iph->ip_dst;
		printf("port %d open  ", ntohs(tcph->source));
		dbg_print_tcp_types(tcph);
	}
	else
		printf("\n");
}

void	*recv_ack(void *ptr)
{
	int					sock;
	char				buff[65536];
	struct sockaddr_in	from;
	socklen_t			fromlen;
	ssize_t				recvret;

	fromlen = sizeof(from);
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if (sock == -1)
	{
		perror("recv sock");
		exit(EXIT_FAILURE);
	}
	while (42)
	{
		ft_bzero(&from, sizeof(from));
		ft_bzero(buff, sizeof(buff));
		puts("wait to recv...");
		recvret = recvfrom(sock, buff, sizeof(buff), 0, (struct sockaddr *)&from, &fromlen);
		process_return(buff, recvret);
	}
 
	close(sock);
	(void)ptr;
	return (NULL);
}
