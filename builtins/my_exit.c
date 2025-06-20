/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:20:33 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/17 16:36:01 by ayameur          ###   ########.fr       */
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
		result = result_tmp * 10 + (*str++ - 48);
		if (result < result_tmp && signe == 1)
			return (-1);
		if (result < result_tmp && signe == -1)
			return (0);
		result_tmp = result;
	}
	return (result * signe);
}
	
int my_exit(t_shell *main, char **cmd)
{
	int		ac;
	long	exit_st;

	ac = len_2d(cmd);
	if (ac == 1)
	{	
		printf("exit\n");
		exit(exite_status);
	}	
	if (!str_is_digit(cmd[1]))
	{
		ft_putstr_fd("numeric argument required\n", 2);
		exit(exit_st);
	}
	if (ac > 2)
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1); 
	}
	exit_st = ft_atoll(cmd[1]);
	if (exit_st > INT_MAX)
		ft_putstr_fd("error\n", 2);
	exit((unsigned char)exit_st);
}
	
void	printf_error(char *var, char* msg, int status)
{
	write(2, "minishell> ", 11);
	if (var)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
	{
		ft_putstr_fd(msg, 2);
	}
	ft_putstr_fd("\n", 2);
	exite_status = status;
	// exit(exite_status);
}

void	cleanup(t_shell *main, int status)
{
	t_cmd *cmd;

	cmd = main->cmd;
	while (cmd)
	{
		if (cmd->in != -1337)
			close(cmd->in);
		if (cmd->out != -1337)
			close(cmd->out);
		cmd = cmd->next;
	}
	exit(exite_status);
}

void	ft_exit(t_shell *main, char *cmd)
{
	struct stat file;
	
	if (stat(cmd, &file) == 0 && S_ISDIR(file.st_mode))
	{	
		printf_error(cmd, "is a directory", 126);
		cleanup(main, 126);
	}
	else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
	{	
		printf_error(cmd, strerror(errno), 126);
		cleanup(main, 126);
	}
	else
	{	
		printf_error(cmd, "commande not found ", 127);
		cleanup(main, 127);
	}
}
