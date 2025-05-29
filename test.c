
#include <stdio.h>
#include <ctype.h>

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}
int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}


int main ()
{
	char *str = "=var";
	int val = ft_isalnum(str[0]);

if (!val) {
    // means: if val is 0 (false), do this
	printf("val = %d\n", val);
    printf("First character is NOT a letter\n");
} 
if (val)
{
    // val is non-zero (true), so the first char IS a letter
	printf("val = %d\n", val);
    printf("First character is a letter\n");
}

}