/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_xmas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:02:15 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/30 16:05:05 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

/*
 *  -= XMAS SCAN =-
 *
 *  Send URG PUSH FIN
 *  Wait for :
 *  	OPEN      no response
 *  	CLOSE     RST & ACK
 *  	FILTERED  impossible
*/

int		xmas_default(void)
{
	return (OPEN);
}

int		xmas_set(enum e_tcp_type types)
{
	if (types & RST && types & ACK)
		return (CLOSE);
	return (xmas_default());
}

void	scan_xmas(char *ipv4name)
{
	int				sock;

	sock = create_socket();

	send_range(sock, g_env.port, ipv4name, URG | PSH | FIN);

	close(sock);
	puts("SCAN XMAS DONE");
}
