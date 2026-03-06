/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 21:01:04 by nalfonso          #+#    #+#             */
/*   Updated: 2026/02/10 18:36:33 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minitalk.h"

static int	ft_alloc_msg(t_state *s)
{
	s->msg = malloc((size_t)s->len + 1);
	if (!s->msg)
		return (1);
	s->msg[s->len] = '\0';
	s->i = 0;
	s->stage = 1;
	s->bit = 0;
	return (0);
}

static void	ft_read_char(t_state *s, int signal)
{
	if (signal == SIGUSR1)
		s->c |= (0x80 >> s->bit);
	s->bit++;
	if (s->bit == CHAR_BIT)
	{
		s->msg[s->i++] = s->c;
		s->c = 0;
		s->bit = 0;
		if (s->i == s->len)
			ft_finish(s);
	}
}

static void	ft_handle_signal(t_state *s, int signal)
{
	if (s->stage == 0)
	{
		ft_read_len(s, signal);
		if (s->bit == 32)
		{
			if (ft_alloc_msg(s))
				ft_reset(s);
		}
	}
	else
		ft_read_char(s, signal);
	Kill(s->client, SIGUSR1);
}

void	ft_handler(int signal, siginfo_t *info, void *context)
{
	static t_state	s;

	(void)context;
	if (info && info->si_pid)
		s.client = info->si_pid;
	ft_handle_signal(&s, signal);
}
int main(void)
{
    __pid_t PID;

    PID = getpid();
    ft_printf("PID : %d \n", PID);
    Signal(SIGUSR1, ft_handler, true);
    Signal(SIGUSR2, ft_handler, true);
    while (252151)
        pause();
    return(0);
}
