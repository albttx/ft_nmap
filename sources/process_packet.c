/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 10:44:15 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/25 10:44:55 by ale-batt         ###   ########.fr       */
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

void		process_return(t_list *port_lst, char buff[], ssize_t size)
{
	struct ip			*iph;
	u_short				iplen;
	struct tcphdr		*tcph;
	struct sockaddr_in	src;
	struct sockaddr_in	dst;

	/*printf("recv %ld ", size);*/
	iph = (struct ip *)buff;
	if (iph->ip_p == IPPROTO_TCP)
	{
		iplen = iph->ip_hl * 4;
		tcph = (struct tcphdr *)(buff + iplen);
		ft_bzero(&src, sizeof(src));
		ft_bzero(&dst, sizeof(dst));
		src.sin_addr = iph->ip_src;
		dst.sin_addr = iph->ip_dst;
		printf("port %d ", ntohs(tcph->source));
		set_in_list(port_lst, ntohs(tcph->source), tcp_to_enum(tcph));
		dbg_print_tcp_types(tcph);
	}
	else
		printf("\n");
}
