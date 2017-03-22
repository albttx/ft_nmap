/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:30:55 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/22 14:20:55 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void	set_ip_header(struct ip *iph, struct sockaddr_in *dest)
{
	iph->ip_hl = sizeof(*iph) >> 2;
	iph->ip_v = IPVERSION;
	iph->ip_tos = 0;
	iph->ip_len = sizeof(struct ip) + sizeof(struct tcphdr);
	iph->ip_id = htons(g_env.id);
	iph->ip_off = htons(16384);
	iph->ip_ttl = 64;
	iph->ip_p = IPPROTO_TCP;
	iph->ip_sum = 0;
	iph->ip_src.s_addr = inet_addr(g_env.source);
	iph->ip_dst = dest->sin_addr;

	iph->ip_sum = csum((unsigned short *)iph, iph->ip_len >> 1);
}

static void	set_tcp_header(struct tcphdr *tcph)
{
	tcph->source = htons(43591);
	tcph->dest = htons(80);
	tcph->seq = htonl(1105024978);
	tcph->ack_seq = 0;
	tcph->doff = sizeof(struct tcphdr) / 4;
	tcph->fin = 0;
	tcph->syn = 1;
	tcph->rst = 0;
	tcph->psh = 0;
	tcph->ack = 0;
	tcph->urg = 0;
	tcph->window = htons(14600);
	tcph->check = 0;
	tcph->urg_ptr = 0;
}

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
	t_peer				peer;
	pthread_t			sniffer_thread;

	ft_bzero(&peer, sizeof(peer));
	peer.sock = create_socket();
	create_thread(&sniffer_thread);
	peer.iph = (struct ip *)peer.buff;
	peer.tcph = (struct tcphdr *)(peer.buff + sizeof(struct ip));

	(peer.dest).sin_family = AF_INET;
	(peer.dest).sin_addr.s_addr = inet_addr(ip->ipv4name);

	set_ip_header(peer.iph, &peer.dest);
	set_tcp_header(peer.tcph);

	scan_syn(&peer);

	pthread_join(sniffer_thread, NULL);
	if (close(peer.sock) < 0)
		perror("close()");
}
