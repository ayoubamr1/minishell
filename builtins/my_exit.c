/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:20:33 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/11 16:26:11 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_is_digit(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[0] != '+' && str[0] != '-' && !ft_isdigit(str[0]))
			return (0);
		i++;
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	len_2d(char **str)
{
	int	i;
	// if (str || !*str)
	// 	return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

long long	ft_atoll(char *str)
{
	int			signe;
	long long	result_tmp;
	long long	result;
	
	signe = 1;
	result = 0;
	result_tmp = 0;
	while (*str == 32 || (*str < 14  && *str > 8))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		signe = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result = result_tmp * 10 + (*str - 48);
		if (result < result_tmp && signe == 1)
			return (-1);
		if (result < result_tmp && signe == -1)
			return (0);
		result_tmp = result;
	}
	return (result * signe);
}

// int	my_exit(t_shell *main, char **cmd)
// {
	
	// int		ac;

	// ac = len_2d(cmd);
	// if (ac == 1)
	// 	(printf("exit\n"), exit(exite_status));
	// else if (ac > 2 && !str_is_digit(cmd[1]))
	// 	return(printf("exit\n to many argument\n"), 1);
	// // else if (ac > 1 && str_is_digit(cmd[1]))
	// // 	return (printf("exit\n"));
	// exite_status = ft_atoll(cmd[1]);
	// if (ft_strlen(cmd[1]) > 1)
	// 	printf("exit\n");
	// printf("exit\n");
	// exit((unsigned char) exite_status);
// }
	
int my_exit(t_shell *main, char **cmd)
{
	int		ac;
	long	exit_status;

	ac = len_2d(cmd);
	printf("exit\n");
	if (ac == 1)
		exit(exite_status);
	if (!str_is_digit(cmd[1]))
	{
		printf("numeric argument required\n");
		exit(exit_status);
	}
	if (ac > 2)
	{
		printf("too many arguments\n");
		return (1); 
	}
	exit_status = ft_atoll(cmd[1]);
	exit((unsigned char)exit_status);
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
// 	t_cmd *curr;
	
// 	curr = main->cmd;
// 	if (!strncmp(curr->cmd[0], "exit", ft_strlen("exit")))
// 	{
// 		ft_malloc(0, FREE);
// 		exit(exite_status);
// 		exite_status = 0;
// 	}
// 	else
// 		exite_status = 1;
// 	return (0);
// }
