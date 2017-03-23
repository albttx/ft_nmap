/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_syn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 15:09:35 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/23 17:44:14 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

/*
 *  -= SYN SCAN =-
 *
 *  Send SYN
 *  Wait for :
 *  	OPEN      SYN & ACK
 *  	CLOSE     RST & ACK
 *  	FILTERED  no response
*/

int		syn_default(void)
{
	return (FILTERED);
}

int		syn_set(enum e_tcp_type types)
{
	if (types & SYN && types & ACK)
		return (OPEN);
	else if (types & RST && types & ACK)
		return (CLOSE);
	return (syn_default());
}

void	scan_syn(char *ipv4name)
{
	int				sock;

	sock = create_socket();

	send_range(sock, g_env.port, ipv4name, SYN);

	close(sock);
}
