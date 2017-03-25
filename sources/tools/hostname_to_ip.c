/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hostname_to_ip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 20:20:42 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/14 20:49:49 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

char	*hostname_to_ip(const char *hostname)
{
	char			*ip;
	struct hostent	*he;
	struct in_addr	**addr_list;

	ip = ft_strnew(INET_ADDRSTRLEN + 1);
	he = gethostbyname(hostname); 
	if (he == NULL)
		return (NULL);
	addr_list = (struct in_addr **)he->h_addr_list;
	ft_strncpy(ip, inet_ntoa(*addr_list[0]), INET_ADDRSTRLEN);
	return (ip);
}
