#include "../../minishell.h"

int	len_n(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = len_n(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	res = ft_malloc(sizeof(char) * (len + 1), MALLOC);
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	while (n > 0)
	{
		res[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}

static	char	*check_delimiter(char *str)
{
	char	*new;
	char	qout;
	int		p;
	int		i;

	new = ft_malloc(ft_strlen(str) + 1, MALLOC);
	i = 0;
	p = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
		{
			(1) && (new[p++] = str[i], qout = str[i++]);
			while (str[i] && str[i] != qout)
				new[p++] = str[i++];
			if (str[i] == qout)
				new[p++] = str[i++];
			new[p] = '\0';
		}
		else if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		else
			new[p++] = str[i++];
	}
	return (new[p] = '\0', remove_quotes (new));
}

// void	handle_heredoc(t_shell *shell, char *delimiter, int fd)
// {
// 	char	*line;
// 	char	*tmp;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || strcmp(line, check_delimiter(delimiter)) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (ft_strchr(line, '$'))
// 		{
// 			tmp = line;
// 			line = ft_expand_token(line, shell->env);
// 			free(tmp);
// 			tmp = NULL;
// 		}
// 		write(fd, line, strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	close (fd);
// }

void	run_heredoc_child(char *delimiter, int write_fd)
{
	char	*line;

	// Restore default SIGINT to allow Ctrl+C kill
	signal(SIGINT, SIG_DFL);

	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);  // Ctrl+D or error

		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}

		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

void	handle_heredoc(t_shell *shell, char *delimiter, int write_fd, t_cmd *node)
{
	pid_t	pid;
	int		status;

	// Ignore SIGINT in parent during heredoc
	signal(SIGINT, SIG_IGN);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(write_fd);
		return;
	}

	if (pid == 0)
	{
		// Child process: handle heredoc input
		run_heredoc_child(delimiter, write_fd);
	}
	else
	{
		// Parent waits for child
		waitpid(pid, &status, 0);

		// Close write_fd from parent (child used it)
		close(write_fd);

		// Restore signal handler for main prompt
		signal(SIGINT, handle_sigint);  // Your custom handler
		signal(SIGQUIT, SIG_IGN);

		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			node->fd_statuts = 911;  // Example flag to abort exec
			exite_status = 130;
		}
	}
}
