/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 10:13:45 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/25 10:25:35 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_STRUCT_H
# define FT_NMAP_STRUCT_H

# include "libft.h"

# include <arpa/inet.h>
# include <netinet/tcp.h>

typedef enum			e_scan_type
{
	S_SYN				= 1,
	S_ACK				= 2,
	S_FIN				= 4,
	S_NUL				= 8,
	S_UDP				= 16,
	S_XMAS				= 32,
}						t_scan_type;

typedef enum			e_tcp_type
{
	SYN 				= 1,
	ACK 				= 2,
	FIN 				= 4,
	RST 				= 8,
	PSH 				= 16,
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

typedef struct			s_port
{
	int					port;
	int					syn_state:2;
	int					ack_state:2;
	int					fin_state:2;
	int					nul_state:2;
	int					udp_state:2;
	int					xmas_state:2;
}						t_port;

#endif
