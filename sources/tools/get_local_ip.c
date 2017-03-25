/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_local_ip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 18:56:07 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/16 19:52:00 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

#define GOOGLE_DNS "8.8.8.8"
#define GOOGLE_DNS_PORT 53

void	get_local_ip(char *buffer)
{
    int					sock;
    struct sockaddr_in	serv;
    struct sockaddr_in	name;
    socklen_t			namelen;
	
	ft_bzero(buffer, INET_ADDRSTRLEN);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
    ft_memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(GOOGLE_DNS);
    serv.sin_port = htons(GOOGLE_DNS_PORT);
 
    if (connect(sock , (const struct sockaddr*)&serv, sizeof(serv)) < 0)
	{
		perror("connect()");
		exit(EXIT_FAILURE);
	}

	namelen = sizeof(name);
    if (getsockname(sock, (struct sockaddr*) &name, &namelen) < 0)
	{
		perror("getsockname");
		exit(EXIT_FAILURE);
	}
 
    if (inet_ntop(AF_INET, &name.sin_addr, buffer, 100) == NULL)
	{
		perror("inet_ntop");
		exit(EXIT_FAILURE);
	}
    close(sock);
}
