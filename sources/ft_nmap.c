/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:32:11 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/30 16:05:18 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void		init_port_list(void)
{
	t_port	port;
	int		i;

	g_env.port_lst = NULL;
	for (i = g_env.port[0]; i <= g_env.port[1]; i++)
	{
		ft_bzero(&port, sizeof(port));
		port.port = i;
		port.syn_state = syn_default();
		port.ack_state = ack_default();
		port.fin_state = fin_default();
		port.nul_state = null_default();
		port.udp_state = CLOSE;
		port.xmas_state = xmas_default();
		ft_lstadd_end(&g_env.port_lst, ft_lstnew(&port, sizeof(port)));
	}
}

int				ft_nmap(void)
{
	t_list	*tmp_ip;
	t_ip	*ip;

	tmp_ip = g_env.ip;
	while (tmp_ip)
	{
		init_port_list();
		ip = tmp_ip->content;
		printf("Start Scan on: %s %s \n", ip->hostname, ip->ipv4name);
		scan(ip);
		ft_lstfree(g_env.port_lst);
		tmp_ip = tmp_ip->next;
	}
	return (1);
}
