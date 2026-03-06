/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_part_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 23:41:07 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/06 00:15:50 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minitalk.h"

void	ft_reset(t_state *s)
{
	s->stage = 0;
	s->len = 0;
	s->i = 0;
	s->bit = 0;
	s->c = 0;
}

void	ft_read_len(t_state *s, int signal)
{
	if (signal == SIGUSR1)
		s->len |= (0x80000000u >> s->bit);
	s->bit++;
}

void	ft_finish(t_state *s)
{
	ft_printf("%s\n", s->msg);
	free(s->msg);
	s->msg = NULL;
	s->stage = 0;
	Kill(s->client, SIGUSR2);
	ft_reset(s);
}

void	ft_initialize(t_client *c)
{
	c->pid = 0;
	c->len = 0;
	c->msg = NULL;
}

int ft_parsing(t_client *c, char *nbr, char *msg)
{
	c->pid = ft_atoi(nbr);
	if (c->pid <= 0)
		return (1);
	c->msg = msg;
	c->len = ft_strlen(msg);
	if (c->len == 0)
	{
		write(2, "Send the correct message\n", 26);
		return (1);
	}
	return (0);

}
