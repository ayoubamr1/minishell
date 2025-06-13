#include "../../minishell.h"

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

static char	*expand_env_var_her(char *str, int *i, t_env *env, char *res)
{
	int		start;
	char	*key;
	char	*val;

	start = 0;
	start = ++(*i);
	while (str[*i] && ft_isalpha(str[*i]) && !is_special_char2(str[*i]))
		(*i)++;
	key = substr(str, start, *i - start);
	val = cher_env(key, env);
	if (!val)
		return(res);
	return (ft_strjoin(res, val));
}

char *heredoc_expand(char *str, t_env *env)
{
	char *res;
	int i;
	
	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
		i += 2;
		else if (str[i] == '$' && str[i + 1] && ft_isalpha(str[i + 1]))
		res = expand_env_var_her(str, &i, env, res);
		else if (str[i] == '$' && str[i + 1] && !ft_isalpha(str[i + 1]))
			res = strjoin_char(res, str[i++]);
		else
			res = strjoin_char(res, str[i++]);
	}
	return (res);
}

void	heredoc_child(char *delimiter, int fd, t_shell *shell)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		i = 1;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, check_delimiter(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$') && i == 0)
		{
			tmp = line;
			line = heredoc_expand(line, shell->env);
			(free(tmp), tmp = NULL);
		}
		write(fd, line, strlen(line));
		(write(fd, "\n", 1), free(line));
	}
	(close(fd), exit(0));
}

void	handle_heredoc(t_shell *shell, char *delimiter, int fd, t_cmd *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd);
		return ;
	}
	if (pid == 0)
		heredoc_child(delimiter, fd, shell);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return ;
		}
		close(fd);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			node->heredoc_statuts = 911;
			exite_status = 130;
		}
	}
}
