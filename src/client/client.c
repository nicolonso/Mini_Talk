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

int ft_atoi_2(char *str)
{
	int	result;
	int	sign;
	
	result = 0;
	sign = 1;
	while (*str == ' '  || (*str >= 9 && *str <= 13))
		str++;
	if(*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - 48);
	return (sign * result);
}

int	ft_strlen_2(char *str)
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
}

void char_bits(int pid, char c)
{
	int i;

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
		usleep(1500);kill(pid, SIGUSR2) == -1		
	}
}



int	main(int ac, char **av)
{
	int	pid;
	int i;

	if (ac == 3)
	{
		if (*av[1] == NULL)
			return (1);
		pid = ft_atoi_2(*av);
		if (pid < 1)
			return (1);
		i = -1;
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR1, signal_handler);
		ft_strlen_2(*av[1]);
		whiel(1)
		{
			
		}
	}
	return (0);
}