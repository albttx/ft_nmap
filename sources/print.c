/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:31:08 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/23 17:29:49 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void		clr_print(int state, char *scan_name)
{
	switch (state)
	{
		case OPEN:
			printf("%s", GREEN);
			break ;
		case FILTERED:
			printf("%s", YELLOW);
			break ;
		case CLOSE:
			printf("%s", RED);
			break ;
	}
	printf("%s %s", scan_name, DEFAULT);
}

static void		print_state(t_port *port)
{
	printf("port %-4d ", port->port);
	if (g_env.type_flags & S_SYN) clr_print(port->syn_state, "SYN");
	if (g_env.type_flags & S_ACK) clr_print(port->ack_state, "ACK");
	if (g_env.type_flags & S_FIN) clr_print(port->fin_state, "FIN");
	if (g_env.type_flags & S_NUL) clr_print(port->nul_state, "NULL");
	if (g_env.type_flags & S_UDP) clr_print(port->udp_state, "UDP");
	if (g_env.type_flags & S_XMAS) clr_print(port->xmas_state, "XMAS");
	printf("\n");
}	

void			print_port_lst(t_list *port_lst)
{
	t_list	*tmp;
	t_port	*port;

	tmp = port_lst;
	printf(" %s OPEN  %s FILTERED  %s CLOSE  %s\n", GREEN, YELLOW, RED, DEFAULT);
	while (tmp)
	{
		port = tmp->content;
		print_state(port);
		tmp = tmp->next;
	}
}
