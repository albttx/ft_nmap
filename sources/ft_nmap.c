/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:32:11 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/15 19:24:07 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void	scan(t_ip *ip)
{
	char	errbuff[PCAP_ERRBUF_SIZE];
	char	*device;
	pcap_t	*descr;

	device = pcap_lookupdev(errbuff);
	if (!device)
	{
		fprintf(stderr, "pcap_lookupdev error: %s\n", errbuff);
		device = ft_strdup("eth0");
		/*return ;*/
	}
	else
		printf("/!\\ WTF IT'S WORKED !!!!\n");

	descr = pcap_open_live(device, BUFSIZ, 1, 1000, errbuff);
	if (!descr)
	{
		fprintf(stderr, "pcap_open_live error: %s\n", errbuff);
		exit(EXIT_FAILURE);
	}
	free(device);
}

int		ft_nmap(void)
{
	t_list	*tmp;
	t_ip	*ip;

	tmp = g_env.ip;
	while (tmp)
	{
		ip = tmp->content;
		printf("Start Scan on: %s %s \n", ip->hostname, ip->ipv4name);
		scan(ip);
		tmp = tmp->next;
	}
	return (1);
}
