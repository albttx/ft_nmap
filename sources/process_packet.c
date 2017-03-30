/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 10:44:15 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/30 18:56:42 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void		set_in_list(t_list *port_lst, int port, enum e_tcp_type types)
{
	t_list	*tmp;
	t_port	*p_port;

	tmp = port_lst;
	while (tmp)
	{
		p_port = tmp->content;
		if (p_port->port == port)
		{
			p_port->syn_state = syn_set(types);
			p_port->ack_state = ack_set(types);
			p_port->fin_state = syn_set(types);
			break ;
		}
		tmp = tmp->next;
	}
}

void	process_packet(u_char *ptr, const struct pcap_pkthdr *pkthdr, const u_char *pkt)
{
	struct ether_header		*ethh;
	struct ip				*iph;
	u_short					iplen;
	struct tcphdr			*tcph;
	struct sockaddr_in		src;
	struct sockaddr_in		dst;

	ethh = (struct ether_header *)pkt;
	iph = (struct ip *)(pkt + sizeof(struct ether_header));
	if (iph->ip_p == IPPROTO_TCP)
	{
		iplen = iph->ip_hl * 4;
		if (iplen < 20)
		{
			printf("ERROR: iplen = %d bytes, packet too small\n", iplen);
			return ;
		}
		tcph = (struct tcphdr *)((void *)pkt + sizeof(*ethh) + iplen);
		ft_bzero(&src, sizeof(src));
		ft_bzero(&dst, sizeof(dst));
		src.sin_addr = iph->ip_src;
		dst.sin_addr = iph->ip_dst;
		printf("port %d ", ntohs(tcph->source));
		printf(" From: %s To: %s \t", inet_ntoa(iph->ip_src), inet_ntoa(iph->ip_dst));
		set_in_list(g_env.port_lst, ntohs(tcph->source), tcp_to_enum(tcph));
		dbg_print_tcp_types(tcph);
	}
}
