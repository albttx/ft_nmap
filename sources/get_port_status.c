/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_port_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:19:32 by ale-batt          #+#    #+#             */
/*   Updated: 2017/08/02 17:49:08 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static int	find_highest(int arr[], int len)
{
	int		i;
	int		high;

	i = 0;
	high = -1;
	while (i < len)
	{
		if (arr[i] > high)
			high = i;
		i++;
	}
	return (high);
}

int		get_port_status(t_port *port)
{
	int		state[3];
	int		status;

	ft_bzero(state, sizeof(state));
	if (g_env.type_flags & S_SYN)
		state[port->syn_state + 1] = port->syn_state;
	else if (g_env.type_flags & S_ACK)
		state[port->ack_state + 1] = port->ack_state;
	else if (g_env.type_flags & S_FIN)
		state[port->fin_state + 1] = port->fin_state;
	else if (g_env.type_flags & S_NUL)
		state[port->nul_state + 1] = port->nul_state;
	else if (g_env.type_flags & S_XMAS)
		state[port->xmas_state + 1] = port->xmas_state;
	status = find_highest(state, 3) - 1;
	return (status);
}
