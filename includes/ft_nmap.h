/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 18:17:35 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/22 20:09:38 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_H
# define FT_NMAP_H

# include "libft.h"

# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <netinet/ip_icmp.h>
# include <pcap/pcap.h>
# include <pthread.h>
# include <signal.h>

#define SYN_FLAGS	SYN | ACK

typedef enum			e_scan_type
{
	S_SYN				= 1,
	S_NUL				= 2,
	S_ACK				= 4,
	S_FIN				= 8,
	S_XMAS				= 16,
	S_UDP				= 32,
}						t_scan_type;

typedef enum			e_tcp_type
{
	SYN 				= 1,
	RST 				= 2,
	FIN 				= 4,
	PSH 				= 8,
	ACK 				= 16,
	URG 				= 32,
}						t_tcp_type;

typedef struct			s_env
{
	t_list				*ip;
	int					port[2];
	int					thread;
	int					id;
	char				source[INET_ADDRSTRLEN];
	enum e_scan_type	type_flags;
}						t_env;

typedef struct			s_ip
{
	char				*hostname;
	char				*ipv4name;
}						t_ip;

typedef struct			s_pseudo_hdr
{
	unsigned int		src_addr;
	unsigned int		dst_addr;
	unsigned char		placeholder;
	unsigned char		protocol;
	unsigned short		tcp_length;
	struct tcphdr		tcp_h;
}						t_pseudo_hdr;

typedef struct			s_peer
{
	int					sock;
	char				buff[4096];
	struct ip			*iph;
	struct tcphdr		*tcph;
	struct sockaddr_in	dest;
}						t_peer;

t_env					g_env;

char					*hostname_to_ip(const char *hostname);
unsigned short			csum(unsigned short *ptr, int nbytes);

int						parser(char **av);
int						ft_nmap(void);

void					set_ip_header(struct ip *iph, struct sockaddr_in *dest);
void					set_tcp_header(struct tcphdr *tcph, enum e_tcp_type flags);
void					set_pseudo_header(t_pseudo_hdr *psh, struct sockaddr_in *dest);
void					set_peer(t_peer *peer, int sock, char *addr);

void					send_range(int sock, int range[], char *hostip, enum e_tcp_type flags);

int						create_socket(void);

void					get_local_ip(char *buffer);

void					scan(t_ip *ip);
void					scan_syn(char *ipv4name);

void					*recv_ack(void *ptr);

void					dbg_print_flags(void);
void					dbg_print_ip(void);
void					dbg_print_port(void);
void					dbg_print_tcp_types(struct tcphdr *tcph);

#endif
