/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_ack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:46:54 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/25 11:51:56 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <poll.h>

void	callback(u_char *ptr, const struct pcap_pkthdr *pkthdr, const u_char *pkt)
{
	struct ether_header		*ethh;
	struct ip				*iph;
	struct tcphdr			*tcph;
	u_short					iplen;
	struct sockaddr_in		src;
	struct sockaddr_in		dst;

	ethh = (struct ether_header *)pkt;
	iph = (struct ip *)(pkt + sizeof(struct ether_header));
	if (iph->ip_p == IPPROTO_TCP)
	{
		iplen = iph->ip_hl * 4;
		if (iplen < 20)
		{
			printf("ERROR: iplen = %d bytes, packet too small\n", iplen);
			return ;
		}
		tcph = (struct tcphdr *)((void *)pkt + sizeof(*ethh) + iplen);
		ft_bzero(&src, sizeof(src));
		ft_bzero(&dst, sizeof(dst));
		src.sin_addr = iph->ip_src;
		dst.sin_addr = iph->ip_dst;
		/*if (ntohs(tcph->source) == 43591)*/
			/*return ;*/
		printf("port %d ", ntohs(tcph->source));
		printf(" From: %s To: %s\n", inet_ntoa(iph->ip_src), inet_ntoa(iph->ip_dst));
		/*set_in_list(port_lst, ntohs(tcph->source), tcp_to_enum(tcph));*/
		dbg_print_tcp_types(tcph);
	}
	/*printf("Receive pkt size %d\n", pkthdr->len);*/
}

static void		listening_pcap(t_list *port_lst)
{
	char				errbuff[PCAP_ERRBUF_SIZE];
	pcap_t				*handle;
	struct bpf_program	fp;
	bpf_u_int32			mask;
	bpf_u_int32			net;
	char filter_exp[] = "tcp";

	if (pcap_lookupnet("eth0", &net, &mask, errbuff) == -1)
	{
		fprintf(stderr, "Can't get netmask for device eth0 err: %s\n", errbuff);
		exit(EXIT_FAILURE);
	}
	handle = pcap_open_live("eth0", 65536, 1, 0, errbuff);
	if (handle == NULL)
	{
		pcap_perror(handle, "pcap_open_live");
		exit(EXIT_FAILURE);
	}
	if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1)
	{
		fprintf(stderr, "Couldn't parse filter %s: %s\n",
				filter_exp, pcap_geterr(handle));
		exit(EXIT_FAILURE);
	}
	if (pcap_setfilter(handle, &fp) == -1)
	{
		fprintf(stderr, "Couldn't install filter %s: %s\n",
				filter_exp, pcap_geterr(handle));
		exit(EXIT_FAILURE);
	}
	if (pcap_dispatch(handle, 1024, callback, NULL) == -1)
	{
		pcap_perror(handle, "pcap_dispatch");
		exit(EXIT_FAILURE);
	}
	pthread_exit(NULL);
}

void			*listener(void *ptr)
{
	/*listening_socket(ptr);*/
	listening_pcap(ptr);
	return (NULL);
}
