/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:15:44 by nalfonso          #+#    #+#             */
/*   Updated: 2025/09/25 21:10:16 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/mini_talk.h"
#include <signal.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void char_bits(int pid, char c, int len)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (j < 32)
	{
		if ((len >> j++) & 1)
			kill (pid, SIGUSR2);
		else
			kill (pid, SIGUSR1);
		usleep(1500);
	}
	while (i < 8)
	{
		if ((c >> i++) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(0);
		}
		else
			if (kill(pid, SIGUSR1) == -1)
				exit(0);
		usleep(1500);// I need to check this line later 	
	}
}

static void	handler_sig(int signal)
{
	if (signal == SIGUSR2)
	{
		ft_printf("Sever recieve the string!\n");
		exit(0);
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int i;
	int len;

	if (ac == 3)
	{
		if (av[1] == NULL)
			return (1);
		pid = ft_atoi(*av);
		if (pid < 1)
			return (1);
		i = -1;
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR1, signal_handler);
		len = ft_strlen((const)*av[1]);
		while(1)
		{
			char_bits(pid, av[1][++i], len);
			if (!av[1][i])
				break ;
		}
		pause();
	}
	return (0);
}
// What is the difference between do it all in the condition if is not 3 values