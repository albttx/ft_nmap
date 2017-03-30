/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_ack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:37:34 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/30 18:37:12 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

/*
 *  -= ACK SCAN =-
 *
 *  Send ACK
 *  Wait for :
 *  	OPEN         impossible
 *  	CLOSE        impossible
 *  	FILTERED     no response
 *  	NO FILTERED  RST
*/

int		ack_default(void)
{
	return (FILTERED);
}

int		ack_set(enum e_tcp_type types)
{
	if (types & RST)
		return (UNFILTERED);
	return (ack_default());
}

void	scan_ack(char *ipv4name)
{
	int				sock;

	sock = create_socket();

	send_range(sock, g_env.port, ipv4name, ACK);

	close(sock);
	puts("SCAN ACK DONE");
}
