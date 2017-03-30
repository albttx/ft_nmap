/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:31:08 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/30 18:50:35 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static char		*port_state_to_str(int state)
{
	if (state == OPEN)
		return ("open");
	else if (state == CLOSE)
		return ("close");
	else if (state == UNFILTERED)
		return ("unfiltred");
	else
		return ("filtered");
}

static int		is_default(t_port *port)
{
	if (port->syn_state == syn_default() &&
		port->ack_state == ack_default() &&
		port->nul_state == null_default() &&
		port->xmas_state == xmas_default() &&
		port->fin_state == fin_default())
	{
		return (1);
	}
	return (-1);
}

static void		clr_print(int state, char *scan_name)
{
	switch (state)
	{
		case OPEN:
			printf("%s", GREEN);
			break ;
		case CLOSE:
			printf("%s", RED);
			break ;
		case FILTERED:
			printf("%s", YELLOW);
			break ;
		case UNFILTERED:
			printf("%s", PURPLE);
			break ;
	}
	printf("%s %s", scan_name, DEFAULT);
}

static void		print_service(int port)
{
	struct servent	*s;

	s = getservbyport(htons(port), "tcp");
	if (s != NULL)
	{
		printf(" %s", s->s_name);
	}
}

static void		print_state(t_port *port)
{
	printf("%-4d |", port->port);
	if (g_env.type_flags & S_SYN) clr_print(port->syn_state, "SYN");
	if (g_env.type_flags & S_ACK) clr_print(port->ack_state, "ACK");
	if (g_env.type_flags & S_FIN) clr_print(port->fin_state, "FIN");
	if (g_env.type_flags & S_NUL) clr_print(port->nul_state, "NULL");
	if (g_env.type_flags & S_UDP) clr_print(port->udp_state, "UDP");
	if (g_env.type_flags & S_XMAS) clr_print(port->xmas_state, "XMAS");
	printf("|");
}	

static void		print_result(t_port *port)
{
	if (g_env.type_flags & S_SYN)
		printf(" %-9s|", port_state_to_str(port->syn_state));
	else if (g_env.type_flags & S_ACK)
		printf(" %-9s|", port_state_to_str(port->ack_state));
}

void			print_port_lst(t_list *port_lst)
{
	t_list	*tmp;
	t_port	*port;
	int		state[3];

	ft_bzero(state, sizeof(state));
	tmp = port_lst;
	puts("-----------------------------------------------------------------");
	printf("Port | Status                   | Result   | Service\n");
	while (tmp)
	{
		port = tmp->content;
		if (is_default(port) == -1)
		{
			print_state(port);
			print_result(port);
			print_service(port->port);
			printf("\n");
		}
		tmp = tmp->next;
	}
}
