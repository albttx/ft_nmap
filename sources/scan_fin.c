/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:37:34 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/24 15:16:13 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

/*
 *  -= FIN SCAN =-
 *
 *  Send FIN
 *  Wait for :
 *  	OPEN      linux: no response | window: 
 *  	CLOSE     RST & ACK
 *  	FILTERED  impossible
*/

int		fin_default(void)
{
	return (OPEN);
}

int		fin_set(enum e_tcp_type types)
{
	if (types & RST && types & ACK)
		return (CLOSE);
	return (fin_default());
}

void	scan_fin(char *ipv4name)
{
	int				sock;

	sock = create_socket();

	send_range(sock, g_env.port, ipv4name, FIN);

	close(sock);
	puts("SCAN FIN DONE");
}
