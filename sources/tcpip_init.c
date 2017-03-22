/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcpip_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:37:46 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/22 20:06:22 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void	set_ip_header(struct ip *iph, struct sockaddr_in *dest)
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

void	set_tcp_header(struct tcphdr *tcph, enum e_tcp_type flags)
{
	tcph->source = htons(43591);
	tcph->dest = htons(80);
	tcph->seq = htonl(1105024978);
	tcph->ack_seq = 0;
	tcph->doff = sizeof(struct tcphdr) / 4;
	tcph->syn = (flags & SYN) ? 1 : 0;
	tcph->rst = (flags & RST) ? 1 : 0;
	tcph->fin = (flags & FIN) ? 1 : 0;
	tcph->psh = (flags & PSH) ? 1 : 0;
	tcph->ack = (flags & ACK) ? 1 : 0;
	tcph->urg = (flags & URG) ? 1 : 0;
	tcph->window = htons(14600);
	tcph->check = 0;
	tcph->urg_ptr = 0;
}

void	set_pseudo_header(t_pseudo_hdr *psh, struct sockaddr_in *dest)
{
	ft_bzero(psh, sizeof(*psh));
	psh->src_addr = inet_addr(g_env.source);
	/*psh->dst_addr = (dest->sin_addr).s_addr;*/
	psh->placeholder = 0;
	psh->protocol = IPPROTO_TCP;
	psh->tcp_length = htons(sizeof(struct tcphdr));
}

void	set_peer(t_peer *peer, int sock, char *addr)
{
	ft_bzero(peer, sizeof(*peer));
	peer->sock = sock;
	peer->iph = (struct ip *)peer->buff;
	peer->tcph = (struct tcphdr *)(peer->buff + sizeof(struct ip));

	(peer->dest).sin_family = AF_INET;
	(peer->dest).sin_addr.s_addr = inet_addr(addr);
}
