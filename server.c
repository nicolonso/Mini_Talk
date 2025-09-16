/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:20:29 by pedro             #+#    #+#             */
/*   Updated: 2025/08/23 19:24:35 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	ft_bzero(void *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

int	bin_to_char(int bin, char *msg)
{
	static int	i;
	static char	c;
	static int	index;

	c |= (bin << i);
	if (i == 7)
	{
		msg[index++] = c;
		if (c == 0)
		{
			ft_printf("%s\n", msg);
			index = 0;
			free(msg);
		}
		i = 0;
		c = 0;
		if (index == 0)
			return (1);
	}
	else
		i++;
	return (0);
}

void	handler_sigusr(int sig, siginfo_t *i)
{
	static char			*msg;
	static unsigned int	len;
	static int			j;
	static int			m;

	if (j < 32)
		len |= (sig << j++);
	else
	{
		if (m++ == 0)
		{
			msg = malloc(len + 1);
			if (!msg)
				exit(0);
		}
		if (bin_to_char(sig == SIGUSR2, msg))
		{
			kill(i->si_pid, SIGUSR2);
			len = 0;
			j = 0;
			m = 0;
		}
		else
			kill(i->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	action;

	pid = getpid();
	ft_printf("PID: %i\n", pid);
	ft_bzero(&action, sizeof(action));
	sigaddset(&action.sa_mask, SIGUSR1);
	sigaddset(&action.sa_mask, SIGUSR2);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = (void *)handler_sigusr;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
}
