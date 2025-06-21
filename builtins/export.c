/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:43 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/20 11:02:56 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int find_equal(char *str)
{
	int i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	is_invalide_indentifer(char **cmd)
{
	int	i;
	
	i = 0;
	if (!is_valid_var(cmd))
		{	
			printf("export: `%s': not a valid identifier\n", cmd[i]);
			return (1);
		}
	return (0);
}

void	plus_equal_add_new(t_shell *main, char **cmd, char *value, int i)
{
	int		eq;
	char	*new_value;
	
	eq = find_equal(cmd[i]);
	// chb3ana leaks
	new_value = substr(cmd[i], 0, eq -1);
	new_value = ft_strjoin(new_value, "=");
	new_value = ft_strjoin(new_value, value);
	// printf("new :%s\n", new_value);
	add_to_env(main, new_value);
}

int	plus_equal_hundle_case(t_shell *main, char **cmd, int i)
{
	char	*value;
	char	*plus_equal;
	t_env	*env;
	size_t	len;
	
	plus_equal = ft_strstr(cmd[i], "+=");
	len = plus_equal - cmd[i];
	value = plus_equal + 2;
	if (len == 0)
		(printf("export: `%s': not a valid identifier\n", cmd[i]), 0);
	env = main->env;
	while (env)
	{
		if (!ft_strncmp(env->content, cmd[i], len) && 
			(env->content[len] == '=' || env->content[len] == '\0'))
		{
			// flag = 1;
			ft_plus_equal(env, cmd, len, value, i);
			return (1) ;
		}
		env = env->next;
	}
	plus_equal_add_new(main, cmd, value, i);
	return (1);
}

int	hundle_equal_case(t_shell *main, char **cmd, int i)
{
	int		flag;
	char	*eq_pos;
	size_t	len;

	flag = 0;
	eq_pos = ft_strchr(cmd[i], '=');
	if (eq_pos)
		len = eq_pos - cmd[i];
	else
		len = ft_strlen(cmd[i]);
	if (len == 0)
		return (printf("export: `%s': not a valid identifier\n", cmd[i]), 0);
	flag = ft_equal(main, cmd, len, i, 0);
	if (!flag)
		add_to_env(main, cmd[i]);
	return (1);
}

void	hundle_no_case(t_shell *main, char **cmd, int i)
{
	t_env	*env;
	size_t	len;

	env = main->env;
	len = ft_strlen(cmd[i]);
	while (env)
	{
		if (!ft_strncmp(env->content, cmd[i], len) && env->content[len] == '=')
			return ;
		env = env->next;
	}
	add_to_env(main, cmd[i]);
}

void	ft_plus_equal(t_env *env, char **cmd, int len, char *value, int i)
{
	char *old_value;
	char *new_value;
	char *new_content;
	
	old_value = env->content + len + 1;
	// printf("old value = %s\n", old_value);
	new_value = ft_strjoin(old_value, value);
	// printf("new value = %s\n", new_value);
	new_content = ft_malloc(len + 1 + ft_strlen(new_value) + 1, MALLOC);
	ft_strncpy(new_content, cmd[i], len);
	new_content[len] = '=';
	// printf("new content befor = %s\n", new_content);
	ft_strcpy(new_value, new_content + len + 1);
	// printf("new content = %s\n", new_content);
	// free(env->content);
	env->content = new_content;
	// free(new_value);         //// need to check it compared to ft_malloc
}

int	ft_equal(t_shell *main, char **cmd, int len, int i, int flag)
{
	t_env *env;

	env = main->env;
	while (env)
	{
		if (!ft_strncmp(env->content, cmd[i], len) && 
			(env->content[len] == '=' || env->content[len] == '\0'))
		{
			printf("dkhal hna\n");
			flag = 1;
			// free(env->content);
			env->content = ft_strdup(cmd[i]);
			break ;
		}
		env = env->next;
	}
	return (flag);
}

int	my_export(t_shell *main, char **cmd)
{
	char	*equal_signe;
	char	*plus_equal;
	int		i;

	i = 1;
	equal_signe = NULL;
	if (!cmd[1])
		return(environment(main->env), 0);
	while (cmd[i])
	{
		if (is_invalide_indentifer(cmd))
			return (0);
		equal_signe = ft_strchr(cmd[i], '=');
		plus_equal = ft_strstr(cmd[i], "+=");
		if (plus_equal && plus_equal == equal_signe - 1)
			plus_equal_hundle_case(main, cmd, i);
		else if (equal_signe)
			hundle_equal_case(main, cmd, i);
		else
			hundle_no_case(main, cmd, i);
		i++;
	}
	return (0);
}

char	**arrange_array(char **array)
{
	int		i;
	int		flag;
	char	*temp;

	i = 0;
	flag = 1;
	while (flag)
	{
		flag = 0;
		i = 0;
		while (array[i + 1])
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				flag = 1;
			}
			i++;
		}
	}
	return (array);
}

// void	environment(t_env *env)
// {
// 	int		i;
// 	int		count;
// 	int		equal_pos;
// 	t_env	*tmp;
// 	char	**array;
	
// 	i = 0;
// 	count = 0;
// 	tmp = env;
// 	while (tmp)
// 	{
// 		count++;
// 		tmp = tmp->next;
// 	}
// 	array = ft_malloc(sizeof (char *) * (count + 1), MALLOC);
// 	if (!array)
// 		return ;
// 	tmp = env;
// 	while (tmp)
// 	{
// 		array[i] = ft_strdup(tmp->content);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	array[i] = NULL; 
// 	array =  arrange_array(array);
// 	i = 0;
// 	while (array[i])
// 	{
// 		// equal_pos = -1;
// 		equal_pos =  search_equal(array, i);
// 		write (1, "declare -x ", 11);
// 		if (equal_pos != -1)
// 		{
// 			// printf("equal_pos = %d\n", equal_pos);
// 			write (1, array[i], equal_pos + 1);
// 			write (1, "\"", 1);
// 			write (1, array[i] + equal_pos + 1, ft_strlen(array[i] + equal_pos + 1));
// 			write (1, "\"\n", 2);	
// 		}
// 		else
// 		{	
// 			// printf("equal_pos = %d\n", equal_pos);
// 			printf("%s\n", array[i]);
// 		}
// 		i++;
// 	}
// }

char	*parse_value(char *str, size_t len)
{
	int		i;
	int		j;
	char	*new_value;

	i = 0;
	j = 0;
	printf("str = %s\n", str);
	new_value = ft_malloc((len + 2), MALLOC);
	if (!new_value)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '+')
		{
			new_value[i] = str[i];
			j++;
		}
		i++;
	}
	new_value[len] = '=';
	new_value[j] = '\0';
	printf("new_value = %s\n", new_value);
	return (new_value);
}

int	search_equal(char **array, int i)
{
	int j;
	int equal_pos;
	
	j = 0;
	equal_pos = -1;
	while (array[i][j])
	{
		if (array[i][j] == '=')
		{
			equal_pos = j;
			break ;
		}
		j++;
	}
	return (equal_pos);
}

int	is_valid_var(char **str)
{
	int i;
	int	j;
	
	i = 1;
	while (str[i])
	{
		j = 0;
		if (!ft_isalpha(str[i][j]) && str[i][j] != '_')
			return (0);
		j++;
		while (str[i][j] && str[i][j] != '=')
		{
			if (str[i][j] == '+')
			{
				if (str[i][j + 1] != '=')
					return (0);
				break ;
			}
			if (!ft_isalpha(str[i][j]) && str[i][j] != '_')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
