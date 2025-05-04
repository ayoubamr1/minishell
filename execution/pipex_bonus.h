/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:20:36 by ayameur           #+#    #+#             */
/*   Updated: 2025/03/14 20:56:30 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex_bonus
{
	int		p[2];
	int		*pid;
	int		in_fd;
	int		out_fd;
	int		nbr_cmd;
	int		here_doc;
	int		infile_fd;
	int		outfile_fd;
	char	**path_env;
	char	***command_array;
}	t_pipex_bonus;

void	count_cmd(t_pipex_bonus *pipe, int ac);
char	**get_path(char **env);
void	ft_init_pipex(int ac, char **av, char **env, t_pipex_bonus *pipex);
void	ft_check_cmds_path(t_pipex_bonus *pipex);
void	ft_execute_cmds(t_pipex_bonus *pipex);
void	ft_creat_pipe(t_pipex_bonus *pipex);
void	ft_fork_process(t_pipex_bonus *pipex, int i);
void	ft_wait_for_children(t_pipex_bonus *pipex);
void	ft_check_command_in_path(t_pipex_bonus *pipex, int i);
void	hundle_here_doc(t_pipex_bonus *pipex, char *delimiter);

char	*ft_strjoin(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
int		ft_strncmp(char	*s1, char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr(char	const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	**ft_split(const char *str, char c);
void	free_command_array(char ***cmd_array);
void	free_2d(char **str);
void	free_previous(t_pipex_bonus *pipex);
void	cleanup_pid(t_pipex_bonus *pipex);
void	free_array(t_pipex_bonus *pipex);
void	close_fds(t_pipex_bonus *pipex);

char	*get_next_line(int fd);
char	*ft_strdup( char *s1);
#endif