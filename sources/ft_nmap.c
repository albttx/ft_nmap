/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:32:11 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/24 15:19:33 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static t_list		*init_port_list(void)
{
	t_list	*port_lst;
	t_port	port;
	int		i;

	port_lst = NULL;
	for (i = g_env.port[0]; i <= g_env.port[1]; i++)
	{
		ft_bzero(&port, sizeof(port));
		port.port = i;
		port.syn_state = syn_default();
		port.ack_state = ack_default();
		port.fin_state = fin_default();
		port.nul_state = OPEN;
		port.udp_state = CLOSE;
		port.xmas_state = OPEN;
		ft_lstadd_end(&port_lst, ft_lstnew(&port, sizeof(port)));
	}
	return (port_lst);
}

int		ft_nmap(void)
{
	t_list	*tmp_ip;
	t_list	*port_lst;
	t_ip	*ip;

	tmp_ip = g_env.ip;
	while (tmp_ip)
	{
		port_lst = init_port_list();
		ip = tmp_ip->content;
		printf("Start Scan on: %s %s \n", ip->hostname, ip->ipv4name);
		scan(ip, port_lst);
		ft_lstfree(port_lst);
		tmp_ip = tmp_ip->next;
	}
	return (1);
}
