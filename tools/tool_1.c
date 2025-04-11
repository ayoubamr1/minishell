#include "../minishell.h"

static	char	*str_cpy(const char *str, char *dest)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	return (str_cpy(s1, dest));
}