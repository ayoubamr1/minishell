#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// #include "minishell.h"

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
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup( char *s1)
{
	char	*ptr;
	size_t	i;

	if (!s1)
		return (NULL);
	i = 0;
	ptr = malloc(ft_strlen(s1) + 1);
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}



char	*ft_itoa(int n)
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

int main()
{
	// fork();
	// int id = fork();
	// if (id != 0)
	// 	fork();
	// printf("hello world\n");
	
	// if (id == 0)
	// 	printf("we are in shild process\n");
	// else
	// 	printf("we are in main process\n");
	char *old = "2";
	char *str;
	str = ft_itoa(atoi(old) + 1);
	printf("%s\n", str);

}