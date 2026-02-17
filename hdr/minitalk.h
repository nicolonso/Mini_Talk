# ifndef MINITALK_H
#define MINITALK_H


// Libraries 
# include <unistd.h>
# include <signal.h>
# include <stdarg.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

# define BUSY   0
# define READY  1

//Printf Function

# define CHEXADECIMAL "0123456789ABCDEF"
# define HEXADECIMAL "0123456789abcdef"

void 	Signal(int sig, void *handler, bool use_siginfo);
void 	Kill(__pid_t pid, int signo);
int 	ft_atoi(char *nbr);
int		ft_strlen(char *str);


typedef unsigned long long	t_number;

int		ft_printf(const char *format, ...);

#endif