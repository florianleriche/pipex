/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleriche <fleriche@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:16:33 by fleriche          #+#    #+#             */
/*   Updated: 2023/02/20 11:19:00 by fleriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], envp);
	if (execve(path, s_cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(0);
	}
}

void	child(char **argv, int *p_fd, char **envp)
{
	int		fd;

	fd = open_file(argv[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(argv[2], envp);
}

void	parent(char **argv, int *p_fd, char **envp)
{
	int		fd;

	fd = open_file(argv[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec(argv[3], envp);
}

int main(int argc, char **argv, char **envp)
{
  int fd[2];
  pid_t pid;
  
  if (argc != 5)
	ft_exit(1);
  if(pipe(fd) == -1)
    exit(-1);
  pid = fork();
  if (pid == -1)
    exit(-1);
  if (!pid)
    child(argv, fd, envp);
  parent(argv, fd, envp);
}