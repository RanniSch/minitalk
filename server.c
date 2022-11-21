/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 05:09:37 by rschlott          #+#    #+#             */
/*   Updated: 2022/11/21 06:34:04 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* writes the mask (f.e. one letter) and sends a signal to the client
void	ft_write_mask(pid_t pid, unsigned int mask)
{
	static int				num_shifts;
	static unsigned char	c;

    if (!mask)
    {
        ft_putendl_fd("\nMessage Received!", 1);
        kill(pid, SIGUSR2);
    }
    else
    {
        ft_putchar_fd(mask, 1);
        kill(pid, SIGUSR1);
    }
}
receives signal from client and transforms with the help of
each signal (8 in total) from one mask, the mask back into f.e. one letter. 
static means, it continues where it stopped
(it exists till the end of the program once initialized). Mask and 
num_shifts are only = 0 before 8 bits arrive. */
void	receive_signal(int sig, siginfo_t *siginfo, void *context)
{
	static int				num_shifts;
	static unsigned char	c;

	if (sig == SIGUSR1)
		c = c + (1 << num_shifts);
	num_shifts++;
	if (num_shifts == 8)
	{
		if (c == 0)
		{
			write(1, "\n", 1);
			kill(siginfo->si_pid, SIGUSR2);
		}
		else
		{
			write(1, &c, 1);
			kill(siginfo->si_pid, SIGUSR1);
		}
		num_shifts = 0;
		c = 0;
	}
	else
		kill(siginfo->si_pid, SIGUSR1);
	(void)context;
}

/* this function handles the signal SIGINT (control + c),
	so that if user terminates the program,
it writes a message. */
void	handle_end(int sig, siginfo_t *info, void *ptr)
{
	(void)sig;
	(void)info;
	(void)ptr;
	ft_putstr_fd("\nProgram terminated by user!\n", 1);
	exit(0);
}

/* struct declared and in it two more things defined. With the SA_SIGINFO flag,
the signals are queued, and they're all delivered. Kill is starting process
to use a signal. For this specific process (with this process ID) function is
called through signal. Who I want to send the message to (kill function with 
the PID and signal) and after what I want to send. */
int	main(void)
{
	struct sigaction	sa;
	struct sigaction	terminate;

	sa = (struct sigaction){.sa_sigaction = receive_signal};
	terminate = (struct sigaction){.sa_sigaction = handle_end};
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	//sa.sa_sigaction = receive_signal;
	sa.sa_flags = SA_SIGINFO;
	//terminate.sa_sigaction = handle_end;
	//terminate.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &terminate, NULL);
	while (1)
		pause();
	return (0);
}
