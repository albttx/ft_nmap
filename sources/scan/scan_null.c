/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:55:52 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/30 16:01:03 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

/*
 *  -= NULL SCAN =-
 *
 *  Send 0
 *  Wait for :
 *  	OPEN      no response
 *  	CLOSE     RST & ACK
 *  	FILTERED  impossible
*/

int		null_default(void)
{
	return (OPEN);
}

int		null_set(enum e_tcp_type types)
{
	if (types & RST && types & ACK)
		return (CLOSE);
	return (null_default());
}

void	scan_null(char *ipv4name)
{
	int				sock;

	sock = create_socket();

	send_range(sock, g_env.port, ipv4name, 0);

	close(sock);
	puts("SCAN NULL DONE");
}
