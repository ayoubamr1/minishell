/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:43 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/09 18:59:32 by ayameur          ###   ########.fr       */
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

void	ft_plus_equal(t_env *env, char **cmd, int len, char *value, int i)
{
	char *old_value;
	char *new_value;
	char *new_content;
	
	old_value = env->content + len + 1;
	printf("old value = %s\n", old_value);
	new_value = ft_strjoin(old_value, value);
	// printf("new value = %s\n", new_value);
	new_content = ft_malloc(len + 1 + ft_strlen(new_value) + 1, MALLOC);
	ft_strncpy(new_content, cmd[i], len);
	new_content[len] = '=';
	// printf("new content befor = %s\n", new_content);
	ft_strcpy(new_value, new_content + len + 1);
	// printf("new content = %s\n", new_content);
	free(env->content);
	env->content = new_content;
	free(new_value);         //// need to check it compared to ft_malloc
}

int	ft_equal(t_shell *main, char **cmd, int len, int i, int flag)
{
	t_env *env;

	env = main->env;
	while (env)
	{
		if (!ft_strncmp(env->content, cmd[i], len) && env->content[len] == '=')
		{
			flag = 1;
			free(env->content);
			env->content = ft_strdup(cmd[i]);
			break ;
		}
		env = env->next;
	}
	return (flag);
}

int	my_export(t_shell *main, char **cmd)
{
	char	*value;
	char	*equal_signe;
	char	*plus_equal;
	char	*old_value;
	char	*new_value;
	char	*new_content;
	t_env	*env;
	int		i;
	int		flag;
	size_t len;

	i = 1;
	flag = 0;
	env = main->env;
	equal_signe = NULL;
	if (!cmd[1])
		environment(env);
	while (cmd[i])
	{
		if (!is_valid_var(cmd))
		{	
			printf("export: `%s': not a valid identifier\n", cmd[i]);
			return (0);
		}
		equal_signe = ft_strchr(cmd[i], '=');
		plus_equal = ft_strstr(cmd[i], "+=");
		if (plus_equal && plus_equal == equal_signe - 1)
		{
			len = plus_equal - cmd[i];
			value = plus_equal + 2;
			if (len == 0)
			{
				printf("export: `%s': not a valid identifier\n", cmd[i]);
				return (0);
			}
			env = main->env;
			while (env)
			{
				if (!ft_strncmp(env->content, cmd[i], len) && env->content[len] == '=')
				{
					flag = 1;
					ft_plus_equal(env, cmd, len, value, i);
					break ;
				}
				env = env->next;
			}
			if (!flag)
			{
				int eq = find_equal(cmd[i]);
				// chb3ana leaks
				new_value = substr(cmd[i], 0, eq -1);
				new_value = ft_strjoin(new_value, "=");
				new_value = ft_strjoin(new_value, value);
				printf("new :%s\n", new_value);
				add_to_env(main, new_value);
			}
		}
		else if (equal_signe)
		{
			// printf("dkhalt hnaaaaa\n");
			len = equal_signe - cmd[i];
			if (len == 0)
			{
				printf("export: `%s': not a valid identifier\n", cmd[i]);
				return (0);
			}
			flag = ft_equal(main, cmd, len, i, flag);
			if (!flag)
				add_to_env(main, cmd[i]);
		}
		// else
			// add_to_export(main, cmd[i]);
		//// hna blan diyal export ahello or a"hello" , i need to add it in export
		i++;
	}
	return (0);
}

void	add_to_export(t_shell *main, char *cmd)
{
	t_env	*env;
	char	**new_array;
	int		equal_pos;
	int		count;
	
	count = 0;
	env = main->env;
	while (env)
	{
		count++;
		env = env->next;
	}
	new_array = malloc(sizeof(char *) * (count + 2));
	env = main->env;
	count = 0;
	while (env)
	{
		new_array[count] = ft_strdup(env->content);
		count++;	
		env = env->next;	
	}
	new_array[count++] = ft_strdup(cmd);
	new_array[count] = NULL;
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

void	environment(t_env *env)
{
	int		i;
	int		count;
	int		equal_pos;
	t_env	*tmp;
	char	**array;
	
	i = 0;
	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	array = malloc(sizeof (char *) * (count + 1));
	if (!array)
		return ;
	tmp = env;
	while (tmp)
	{
		array[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL; 
	array =  arrange_array(array);
	i = 0;
	while (array[i])
	{
		// equal_pos = -1;
		equal_pos =  search_equal(array, i);
		write (1, "declare -x ", 11);
		if (equal_pos != -1)
		{
			// printf("equal_pos = %d\n", equal_pos);
			write (1, array[i], equal_pos + 1);
			write (1, "\"", 1);
			write (1, array[i] + equal_pos + 1, ft_strlen(array[i] + equal_pos + 1));
			write (1, "\"\n", 2);	
		}
		else
		{	
			// printf("equal_pos = %d\n", equal_pos);
			printf("%s\n", array[i]);
		}
		i++;
	}
}

char	*parse_value(char *str, size_t len)
{
	int		i;
	int		j;
	char	*new_value;

	i = 0;
	j = 0;
	printf("str = %s\n", str);
	new_value = malloc(len + 2);
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

// void	add_var(t_shell *main)
// {
// 	t_env *curr;

// 	curr = main->env;
// 	while (curr)
// 	{
		
// 	}
// }

int	is_valid_var(char **str)
{
	int i;
	int	j;
	
	i = 1;
	if (!str || !*str)
		return (0);
	// if (!ft_isalpha(str[0][0]) && str[0][0] != '_')
	// 	return (0);
	while (str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] != '=' && str[i][j] != '+' && str[i][j] != '_')
		{
			// if (str[i][0] == '_')
			// 	j++;
			if (!ft_isalpha(str[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


















// void	export(char	*input, char **env)//t_shell *main_struct)
// {
// 	char	var_name[100];
// 	char	*value;
// 	int 	i;
// 	int		j;
	
// 	j = 0;
// 	while (input[j])
// 	{
// 		if (input[j] == '$')
// 		{	
// 			j++;
// 			i = 0;
// 			while (input[j] && (ft_isalnum(input[j]) || input[j] == '_' ))
// 				var_name[i++] = input[j++];
// 			var_name[i] = '\0';
// 			value = my_getenv(env, var_name); // main_struct
// 			if (value)
// 				printf("%s", value);
// 		}
// 		else
// 		{
// 			ft_putchar(input[j]);
// 			j++;
// 		}
// 	}
// 	printf("\n");
// 	// if (av[1] == NULL)
// 	// {
// 	// 	fprintf(stderr, "missigne argument"); // need to change
// 	// 	return (NULL);
// 	// }
// 	// name = ft_split(av[1], '='); // if we need to export a lot of variable int the same commande line, 
// 	// 							 //	we need to creat a 3D array
// 	// 							 // and allocate for each 2D array that return split inside 
// 	// 							 // 3D array
// 	// if (name == NULL || name[0] == NULL || name[1] == NULL)
// 	// {
// 	// 	fprintf(stderr, "export : invalid format"); // need to change 
// 	// 	return (NULL);
// 	// }
// 	// return (name);
// 	// // need to update in my enviroment variable
// }

// int main (int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	// t_shell *env = NULL;
// 	// (void)ac;
// 	// export("hello $USER, you home is $HOME");
// 	export("somethis=ayoub", env);
// 	// int i = 0;
// 	// while (s[i])
// 	// {
// 	// 	printf("[%s][%p]\n", s[i], &s[i]);
// 	// 	i++;
// 	// }
// }