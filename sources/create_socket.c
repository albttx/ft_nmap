/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_socket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 15:24:25 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/20 12:32:06 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static int	set_sockopt(int sock)
{
	int		on;

	on = 1;
	// Tell the Kernel that headers are included in the packet
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof (on)) < 0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	return (sock);
}

int			create_socket(void)
{
	int		sock;

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if (sock == -1)
	{
		perror("Socket()");
		exit(EXIT_FAILURE);
	}
	set_sockopt(sock);
	return (sock);
}
