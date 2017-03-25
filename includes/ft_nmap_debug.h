/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_debug.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 10:20:38 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/25 10:25:14 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_DEBUG_H
# define FT_NMAP_DEBUG_H

void	dbg_print_flags(void);
void	dbg_print_ip(void);
void	dbg_print_port(void);
void	dbg_print_tcp_types(struct tcphdr *tcph);

#endif
