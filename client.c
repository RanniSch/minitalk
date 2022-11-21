/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 05:09:33 by rschlott          #+#    #+#             */
/*   Updated: 2022/11/21 06:34:11 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int			g_received;

/* with the help of my defined mask and the & operator, I can
send a string to the server. */
static void	send_signal(int pid, char *str)
{
	int	num_shifts;
	int	i;
	int	len;

	//int mask;
	i = -1;
	len = ft_strlen(str);
	while (++i <= len)
	{
		//mask = 0b10000000;
		num_shifts = 0;
		while (num_shifts < 8)
		{
			g_received = 0;
			if (str[i] >> num_shifts & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			//mask = mask >> 1;
			num_shifts++;
			while (g_received == 0)
				pause();
		}
	}
}

/* receiving signal from server; if no signal "Server PID must be correct" */
void	get_res(int sig, siginfo_t *siginfo, void *context)
{
	static int	count;

	if (sig == SIGUSR1)
		count++;
	else
	{
		count++;
		ft_putstr_fd("Received ", 1);
		ft_putnbr_fd(count, 1);
		ft_putstr_fd(" responses (Signals) from Server.\n", 1);
		exit(0);
	}
	g_received = 1;
	(void)siginfo;
	(void)context;
}

/* examines and changes both signals and then sending signal to a process */
int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa = (struct sigaction){.sa_sigaction = get_res};
	g_received = 1;
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr_fd("Insert: ./client [SERVER-PID] [\"STRING\"]\n", 1);
		return (1);
	}
	//signal(SIGUSR1, handler);
	//signal(SIGUSR2, handler);
	//sa.sa_sigaction = get_res;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_signal(ft_atoi(argv[1]), argv[2]);
	return (0);
}
