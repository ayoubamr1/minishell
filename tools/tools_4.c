#include "../minishell.h"

// int	ft_isalnum(int c)
// {
// 	return (ft_isdigit(c) || ft_isalpha(c));
// }

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

// int ft_isspace(int c)
// {
// 	if (c == ' ' || c == '\t' || c == '\n')
//     	return 1;
// 	return 0;
// }
