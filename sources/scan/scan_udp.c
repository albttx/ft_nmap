/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_udp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:22:03 by ale-batt          #+#    #+#             */
/*   Updated: 2017/08/02 17:30:33 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

/*
 *  -= ACK SCAN =-
 *
 *  Send ACK
 *  Wait for :
 *  	OPEN         no response
 *  	FILTERED     impossible (no response)
 *  	CLOSE        ICMP port unreachable
*/

int		udp_default(void)
{
	return (OPEN);
}

int		udp_set(enum e_tcp_type types)
{
	return (udp_default());
}

void	scan_udp(char *ipv4name)
{

}
