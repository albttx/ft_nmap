/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_scan.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 10:22:09 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/30 16:06:19 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_SCAN_H
# define FT_NMAP_SCAN_H

void	scan(t_ip *ip);

void	scan_syn(char *ipv4name);
int		syn_set(enum e_tcp_type types);
int		syn_default(void);

void	scan_fin(char *ipv4name);
int		fin_set(enum e_tcp_type types);
int		fin_default(void);

void	scan_ack(char *ipv4name);
int		ack_set(enum e_tcp_type types);
int		ack_default(void);

void	scan_null(char *ipv4name);
int		null_set(enum e_tcp_type types);
int		null_default(void);

void	scan_xmas(char *ipv4name);
int		xmas_set(enum e_tcp_type types);
int		xmas_default(void);

#endif
