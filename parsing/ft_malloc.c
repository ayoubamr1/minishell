#include "../minishell.h"


void	ft_lstclear(t_token **lst)
{
	t_token	*n;

	if (!lst)
		return ;
	while (*lst)
	{
		n = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = n;
	}
	*lst = NULL;
}
void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*final;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	final = ft_lstlast(*lst);
	final->next = new;
	return ;
}
t_token	*ft_lstnew(void *content)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
void	ft_malloc(size_t nb, t_token **token, int i, int k, int p)
{
	 
	t_token *new;
	void *mlc;
	mlc = malloc(nb);
	new = ft_lstnew(mlc);
	ft_lstadd_back(token, new);
}
int main()
{
	t_token *token;
	char *str = "hello";
	
	printf("%p");
}