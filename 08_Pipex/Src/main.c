/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-tuto <lle-tuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:23:01 by lle-tuto          #+#    #+#             */
/*   Updated: 2025/03/12 09:30:55 by lle-tuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_forks(t_pipe *all, char **args, char **envp, int path_nb)
{
	if (all->fd_in == -1 || all->fd_out == -1)
		return (free_tab(&args), free_all(all), exit(all->error));
	dup2(all->fd_in, STDIN_FILENO);
	dup2(all->pipefd[1], STDOUT_FILENO);
	close(all->pipefd[0]);
	close(all->pipefd[1]);
	close(all->fd_in);
	close(all->fd_out);
	if (!all->paths[path_nb])
		return (free_tab(&args), free_all(all), exit(127));
	if (execve(all->paths[path_nb], args, envp) == -1)
		return (free_tab(&args), free_all(all), perror("execve"), exit(126));
}

static void	last_fork(t_pipe *all, char **args, char **envp, int path_nb)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (all->fd_in == -1 || all->fd_out == -1)
			return (free_tab(&args), free_all(all), exit(all->error));
		dup2(all->fd_in, STDIN_FILENO);
		dup2(all->fd_out, STDOUT_FILENO);
		close(all->fd_in);
		close(all->fd_out);
		if (!all->paths[path_nb])
			return (free_tab(&args), free_all(all), exit(127));
		if (execve(all->paths[path_nb], args, envp) == -1)
			return (free_tab(&args), free_all(all), perror("execve"),
				exit(126));
	}
	else if (pid < 0)
		return (free_all(all), perror("fork"), exit(EXIT_FAILURE));
	close(all->fd_in);
	close(all->fd_out);
}

static void	create_fork(t_pipe *all, int path_nb, char **argv, char **envp)
{
	pid_t	pid;
	char	**args;

	args = max_split(argv[path_nb + 2], ' ', '\'');
	if (!args)
		return (free_all(all), exit(EXIT_FAILURE));
	if (pipe(all->pipefd) == -1)
		return (free_all(all), perror("pipe"), exit(EXIT_FAILURE));
	pid = fork();
	if (pid == 0)
		first_forks(all, args, envp, path_nb);
	else if (pid < 0)
		return (free_all(all), perror("fork"), exit(EXIT_FAILURE));
	free_tab(&args);
	close(all->pipefd[1]);
	close(all->fd_in);
	all->fd_in = all->pipefd[0];
}

static int	begin(char **argv, int argc, char **envp)
{
	t_pipe	all;
	int		path_nb;
	int		status;
	char	**args;

	path_nb = 0;
	all = init_struct(argv, argc, envp);
	while ((path_nb + 2) < argc - 2)
	{
		create_fork(&all, path_nb, argv, envp);
		path_nb++;
	}
	args = max_split(argv[path_nb + 2], ' ', '\'');
	if (!args)
		return (free_all(&all), exit(EXIT_FAILURE), -1);
	last_fork(&all, args, envp, path_nb);
	free_tab(&args);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			all.error = WEXITSTATUS(status);
	}
	free_all(&all);
	return (all.error);
}

int	main(int argc, char **argv, char **envp)
{
	int	error;

	error = 0;
	if (argc != 5)
	{
		putstr2("Error: Bad arguments\n");
		return (1);
	}
	error = begin(argv, argc, envp);
	return (error);
}
