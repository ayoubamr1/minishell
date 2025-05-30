/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:43 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/30 18:45:56 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	my_export(t_shell *main, char *var)
// {
// 	t_env	*curr;
// 	size_t	len;
// 	char	*new_var;
// 	char	*signe_equal;
// 	char	buffer[256];
// 	char	*value;
// 	int		i;
	
// 	i = 0;
// 	if (!is_valid_var(var))
// 	{	
// 		printf("export: `%s': not a valid identifier\n", var);
// 		return ;
// 	}
// 	signe_equal = ft_strchr(var, '=');
// 	if (!signe_equal)
// 	{	
// 		printf("====== is NULL======\n");
// 		return ;
// 	}
// 	// printf("signe equal = %s\n", signe_equal);
// 	len = signe_equal - var;
// 	// printf("len export = %ld\n", len);
// 	ft_strncpy(buffer, var, len);
// 	buffer[len] = '\0';
// 	printf("buffer = %s\n", buffer);
// 	value = signe_equal + 1;
// 	printf("value = %s\n", value);
// 	curr = main->env;
// 	new_var = malloc(ft_strlen(var) + 1);
// 	if (!new_var)
// 		return;
// 	ft_strcpy(var, new_var);
// 	// printf("new_var = %s\n", new_var);
// 	while (curr)
// 	{
// 		if (ft_strncmp(curr->content, buffer, len) == 0 && curr->content[len] == '=')
// 		{
// 			// printf("===============\n");
// 			free(curr->content);
// 			curr->content = new_var;
// 			return ;
// 		}
// 		curr = curr->next;
// 	}
// 	add_to_env(main, new_var);
// }

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

void	my_export(t_shell *main, char **cmd)
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
	if (!cmd[1])
		environment(env);
	while (cmd[i])
	{
		equal_signe = ft_strchr(cmd[i], '=');
		printf("equal signe = %s\n", equal_signe);
		plus_equal = ft_strstr(cmd[i], "+=");
		printf("plus equal = %s\n", plus_equal);
		if (plus_equal && plus_equal == equal_signe - 1)
		{
			len = plus_equal - cmd[i];
			printf("len = %ld\n", len);
			value = plus_equal + 2;
			printf("value = %s\n", value);
			env = main->env;
			while (env)
			{
				if (!ft_strncmp(env->content, cmd[i], len) && env->content[len] == '=')
				{
					flag = 1;
					printf("dkhaal hnaa\n");
					old_value = env->content + len + 1;
					printf("old value = %s\n", old_value);
					new_value = ft_strjoin(old_value, value);
					printf("new value = %s\n", new_value);
					new_content = malloc(len + 1 + ft_strlen(new_value) + 1);
					ft_strncpy(new_content, cmd[i], len);
					new_content[len] = '=';
					printf("new content befor = %s\n", new_content);
					ft_strcpy(new_value, new_content + len + 1);
					printf("new content = %s\n", new_content);
					free(env->content);
					env->content = new_content;
					free(new_value);
					break ;
				}
				env = env->next;
			}
			if (!flag)
			{
				// printf("cmd[%d] = %s\n", i ,cmd[i]);
				// new_value = parse_value(cmd[i], len);
				int eq = find_equal(cmd[i]);
				// chb3ana leaks
				new_value = substr(cmd[i], 0, eq -1);
				new_value = ft_strjoin(new_value, "=");
				printf("new :%s", new_value);
				add_to_env(main, new_value);
			}
			// else
			// 	add_to_env(main, new_value);
		}
		else if (equal_signe)
		{
			// printf("dkhalt hnaaaaa\n");
			len = equal_signe - cmd[i];
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
			if (!flag)
				add_to_env(main, cmd[i]);
		}
		i++;
	}
}

void	environment(t_env *env)
{
	while (env)
	{
		printf("declare -x %s\n", env->content);
		env = env->next;
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

// int	check_equal(char *cmd)
// {
// 	int	i;
	
// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '+')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// void	add_var(t_shell *main)
// {
// 	t_env *curr;

// 	curr = main->env;
// 	while (curr)
// 	{
		
// 	}
// }

int	is_valid_var(char *str)
{
	int i;
	
	i = 1;
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
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