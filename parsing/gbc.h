#ifndef GBC_H
# define GBC_H

typedef struct s_list
{
	void			*ptr;
	struct s_list	*next;
}	t_list;

typedef enum e_call
{
	FREE,
	MALLOC
}	t_call;

t_list	*new_node(void	*ptr);
t_list	*last_node(t_list **head);
void	add_back(t_list	**head, t_list *new);
void	clear_all(t_list **head);
void	*ft_malloc(size_t size, t_call call);
#endif
