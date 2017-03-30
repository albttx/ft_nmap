/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_ack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:46:54 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/30 15:53:12 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void		set_filter(pcap_t *handle, bpf_u_int32 net)
{
	char				filter_exp[100];
	struct bpf_program	fp;

	snprintf(filter_exp, 100, "((tcp) and (dst host %s))", g_env.source);
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
	pcap_freecode(&fp);
}

static void		receiver(pcap_t *handle)
{
	int		cc;
	int		count;

	cc = 1;
	count = 0;
	while (cc >= 0 && count < 2)
	{
		cc = pcap_dispatch(handle, -1, &process_packet, NULL);
		/*printf("cc = %d \n", cc);*/
		if (cc == 0)
			count++;
		if (cc == -1)
		{
			pcap_perror(handle, "pcap_dispatch");
			exit(EXIT_FAILURE);
		}
		else if (cc == -2)
			break ;
	}
}

static void		listening_pcap(void)
{
	char				errbuff[PCAP_ERRBUF_SIZE];
	pcap_t				*handle;
	bpf_u_int32			net;
	bpf_u_int32			mask;

	if (pcap_lookupnet("eth0", &net, &mask, errbuff) == -1)
	{
		fprintf(stderr, "Can't get netmask for device eth0 err: %s\n", errbuff);
		exit(EXIT_FAILURE);
	}
	handle = pcap_open_live("eth0", 65536, 1, 1000, errbuff);
	if (handle == NULL)
	{
		pcap_perror(handle, errbuff);
		exit(EXIT_FAILURE);
	}
	set_filter(handle, net);
	receiver(handle);

	pcap_close(handle);
	pthread_exit(NULL);
}

void			*listener(void *ptr)
{
	listening_pcap();
	(void)ptr;
	return (NULL);
}
