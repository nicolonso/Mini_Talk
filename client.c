/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:20:37 by pedro             #+#    #+#             */
/*   Updated: 2025/08/20 16:02:03 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

void	char_to_bin(int pid, char c)
{
	int	i;

	i = 0;
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
		usleep(1500);
	}
}

void	handler_sigusr(int sig)
{
	if (sig == SIGUSR2)
	{
		ft_printf("Servidor recebeu a string!\n");
		exit(0);
	}
}

void	ft_strlen(char *str, int pid)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[len])
		len++;
	while (i < 32)
	{
		if ((len >> i++) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(1500);
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
		return (0);
	pid = ft_atoi(av[1]);
	i = 0;
	if (pid < 1)
		return (0);
	signal(SIGUSR1, handler_sigusr);
	signal(SIGUSR2, handler_sigusr);
	ft_strlen(av[2], pid);
	while (1)
	{
		char_to_bin(pid, av[2][i]);
		if (!av[2][i])
			break ;
		i++;
	}
	pause();
	return (0);
}
