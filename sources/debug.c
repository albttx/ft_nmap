/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 12:22:18 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/22 15:00:48 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void	dbg_print_flags(void)
{
	(g_env.type_flags & SYN) ? printf("%sSYN ", GREEN) : printf("%sSYN ", RED);
	(g_env.type_flags & NUL) ? printf("%sNULL ", GREEN) : printf("%sNULL ", RED);
	(g_env.type_flags & ACK) ? printf("%sACK ", GREEN) : printf("%sACK ", RED);
	(g_env.type_flags & FIN) ? printf("%sFIN ", GREEN) : printf("%sFIN ", RED);
	(g_env.type_flags & XMAS) ? printf("%sXMAS ", GREEN) : printf("%sXMAS ", RED);
	(g_env.type_flags & UDP) ? printf("%sUDP", GREEN) : printf("%sUDP", RED);
	printf("%s\n", DEFAULT);
}

void	dbg_print_ip(void)
{
	t_list	*tmp;
	t_ip	*ip;

	tmp = g_env.ip;
	printf("List of IPs:\n");
	while (tmp)
	{
		ip = tmp->content;
		printf("    %-16s %s\n", ip->ipv4name, ip->hostname);
		tmp = tmp->next;
	}
}

void	dbg_print_port(void)
{
	printf("Port %d to %d\n", g_env.port[0], g_env.port[1]);
}

void	dbg_print_tcp_types(struct tcphdr *tcph)
{
	(tcph->syn == 1) ? printf("%sSYN ", GREEN) : printf("%sSYN ", RED);
	(tcph->ack == 1) ? printf("%sACK ", GREEN) : printf("%sACK ", RED);
	(tcph->fin == 1) ? printf("%sFIN ", GREEN) : printf("%sFIN ", RED);
	(tcph->rst == 1) ? printf("%sRST ", GREEN) : printf("%sRST ", RED);
	(tcph->psh == 1) ? printf("%sPSH ", GREEN) : printf("%sPSH ", RED);
	(tcph->urg == 1) ? printf("%sURG ", GREEN) : printf("%sURG ", RED);
	printf("%s\n", DEFAULT);
}
