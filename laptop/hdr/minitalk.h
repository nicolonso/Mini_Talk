# ifndef MINITALK_H
#define MINITALK_H


// Libraries 
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdarg.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

# define BUSY   0
# define READY  1


void Signal(int sig, void *handler, bool use_siginfo);
void Kill(__pid_t pid, int signo);
int ft_atoi(char *nbr);

#endif