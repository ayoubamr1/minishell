#include "../../minishell.h"

static	int	len_n(int n)
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
static char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = len_n(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
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

// static int	handle_heredoc(char	*delimiter) 
// {
// 	static size_t hrc_pid = 0;

// 	if (hrc_pid == 0)
// 		hrc_pid = getpid();
// 	else
// 		hrc_pid++;

// 	// Generate filename
// 	char *id_str = ft_itoa(hrc_pid);
// 	char *filepath = ft_strjoin("/tmp/", id_str);
// 	free(id_str);

// 	int fd = open(filepath, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		free(filepath);
// 		return (-1);
// 	}

// 	while (1)
// 	{
// 		char *line = readline("> ");
// 		if (!line || strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		write(fd, line, strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	free(filepath);
// 	char *str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("[%s]\n", str);
// 		str = get_next_line(fd);
// 	}
// 	return (fd); // Return file descriptor to read from later
// }

static char	*expand_pid(char *res, char *str, int i)
{
	pid_t	pid;
	char	*pid_str;
	char	*tmp;
	int		start;

	start = i;
	// i = i + 2;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			// printf(">>[%s]\n", substr(str, start, i - start));
			// printf(">>[%s]\n",res);
			// printf(">>[%s]\n",ft_strjoin(res, substr(str, start, i - start)));
			return(ft_strjoin(res, substr(str, start, i - start)));
		}
		i++;
	}
	pid = getpid();
	pid_str = id_itoa(pid);
	if (!pid_str)
		return (res);
	tmp = ft_strjoin(res, pid_str);
	return (tmp);
}

static char	*cher_env(char *key, t_env *env)
{
	t_env	*tmp;
	char	*search;
	size_t	key_len;

	tmp = env;
	// search = ft_strjoin(key, ft_strdup("="));
	key_len = strlen(key);

	while (tmp)
	{
		if (!ft_strncmp(tmp->content, key, key_len))
		{
			return (ft_strdup(tmp->content + key_len));
		}		
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

// static int	is_special_charr(char c)
// {
// 	return (c == '|' || c == '<' || c == '>' || c == '"' || c == '\'' || c == ' ' || c == '$');
// }

static int	is_special_charr(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ' || c == '$');
}

static char	*expand_env_var(char *str, int *i, t_env *env, char *res)
{
	int		start;
	char	*key;
	char	*val;
	char	*tmp;
	char 	*env_path;
	int		j;
	int		k;
	int 	p;
	char	quot = 0;
	k = 0;
	while (str[k] && k <= (*i))
	{
		if ((str[k] == '\'' || str[k] == '"') && quot == 0)
			quot = str[k];
		else if (str[k] == quot)
			quot = 0;
		k++;
	}
	start = ++(*i);
	j = 0;
	while (str[*i] && ft_isalpha(str[*i]) && !is_special_charr(str[*i]))
		(*i)++;
	key = substr(str, start, *i - start);
	val = cher_env(key, env);
	if (quot == '\'')
		return(ft_strjoin(res, ft_strjoin("$", key)));
	if (val)
	{
		env_path = ft_malloc(ft_strlen(val) + 1, MALLOC);
		while (val[j] && val[j] != '=')
			j++;
		if (val[j])
			j++;
		p = 0;
		while (val[j])
			env_path[p++] = val[j++];
		env_path[p] = '\0';
	}
	tmp = ft_strjoin(res, env_path);
	// you can remove tmp and k
	return (tmp);
}

static char *ft_dolar(char *str)
{
	int i;
	int p;
	char *new;
	char qout;

	if (!str)
		return(NULL);
	new = ft_malloc(ft_strlen(str) + 1, MALLOC);
	(1) && (i = 0, p = 0);
	while (str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
		{
			qout = str[i];
			new[p++] = str[i++];
			while (str[i] && str[i] != qout)
				new[p++] = str[i++];
			if (str[i] == qout)
				new[p++] = str[i++];
		}
		else if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		else
			new[p++] = str[i++];
	}
	new[p] = '\0';
	return(new);
}

// static char *ft_dolar(char *str)
// {
//     int i = 0;
//     int p = 0;
//     char *new;
//     char qout;

//     new = ft_malloc(ft_strlen(str) + 1, MALLOC);
//     if (!new)
//         return NULL;

//     while (str[i])
//     {
//         if (str[i] == '"' || str[i] == '\'')
//         {
//             qout = str[i++];
//             while (str[i] && str[i] != qout)
//                 new[p++] = str[i++];
//             if (str[i] == qout)
//                 i++; // skip closing quote
//         }
//         else if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
//         {
//             i++; // skip the dollar sign
//         }
//         else
//         {
//             new[p++] = str[i++];
//         }
//     }
//     new[p] = '\0';
//     printf("new>[%s]\n", new);

//     return new;
// }


// char	*ft_expand_token(char *str, t_env *env)
// {
// 	int		i;
// 	char	*res;
// 	char	*tmp;

// 	i = 0;
// 	res = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] == '$')
// 		{
// 			res = expand_pid(res, str, i);
// 			i += 2;
// 		}
// 		else if (str[i] && (str[i] == '$') && str[i + 1] && ft_isalpha(str[i + 1]))
// 			res = expand_env_var(str, &i, env, res);
// 		else
// 		{
// 			tmp = substr(str, i, 1);
// 			res = ft_strjoin(res, tmp);
// 			i++;
// 		}
// 	}
// 		// printf("res=>[%s]\n", res);
// 	return (ft_dolar(res));
// }

char *handle_heredoc(t_shell *shell, char *delimiter)
{
	// static size_t	hrc_pid;
	char			*id_str;
	char			*filepath;
	int				fd;

	static size_t hrc_pid = 0;
	if (hrc_pid == 0)
		hrc_pid = getpid();
	else
		hrc_pid++;
	id_str = ft_itoa(hrc_pid);
	filepath = ft_strjoin("/tmp/", id_str);
	// printf("filepath = %s\n", filepath);
	free(id_str);
	fd = open(filepath, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (NULL);
	}
	while (1)
	{
		char *line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		// line = ft_expand_token(line, env);
		int i = 0;
		while (line[i])
		{
			if (line[i] == '$')
			{
				line = ft_expand_token(line, shell->env);
				break;
			}
			i++;
		}
			
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	// lseek(fd, 0, SEEK_SET);
	return (filepath);
}
