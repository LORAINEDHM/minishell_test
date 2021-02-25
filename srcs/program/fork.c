#include "../minishell.h"

static void	ms_read_pipe(t_cmd *cmd, int fd[2])
{
	int		ret;
	char	buff[2];
	char	*str;
	char	*temp;

	str = NULL;
	// printf("hello\n");
	while ((ret = read(fd[0], buff, 1)) > 0)
	{	
		// printf("str2 = %s\n", str);
		buff[ret] = '\0';
		temp = str;
		// printf("temp = %s\n", temp);
		// printf("buff = %s\n", buff);
		if (temp != NULL)
		{
			str = ft_strjoin(temp, buff);
			free (temp);
		}
		else 
			str = ft_strdup(buff);
		// printf("str = %s\n", str);
		// if (temp != NULL)
		// 	free (temp);
	}
	cmd->inputdata = str;
	// printf("\n inputdata = %s\n\n", cmd->inputdata);
}

static void	ms_parent(t_allcmd *allcmd, int fd[2], t_cmd *cmd)
{
	wait(NULL); // peut être optionel
	// printf("Hi dad!\n");
	close(fd[1]);
	ms_read_pipe(cmd, fd);
	close(fd[0]);
	ms_redirections(cmd, allcmd);
	ms_builtins(cmd, allcmd);
	dup2(cmd->fd, 1);
	cmd->fd = -1;


	// if (ft_check_redirections(data, data->cmd_tab[data->a], data->path) == -1)
	// 	return ;
	// ft_do_redirections(data);
	// ft_redirect_chevron(data);
	// ft_hub(data, data->cmd_tab[data->a]->cmd);
}

static void	ms_child(t_allcmd *allcmd, int fd[2], t_cmd *cmd)
{
	// printf("Hi kid!\n");
	// printf("allcmd->next %p\n",allcmd->next);
	close(fd[0]);
	dup2(fd[1], 1); 
	close(fd[1]);
	if (allcmd->next == NULL)
		exit(0);
	else
	{
		// printf("lolo 2= %s\n", allcmd->next->cmd);
		ms_fork(allcmd->next, cmd);
	}
}

int     ms_fork(t_allcmd *allcmd, t_cmd *cmd)
{
    pid_t   pid;
    int     fd[2];

	printf("coucou\n");
    pipe (fd);
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE); // c'est pas bon mais temporaire
    else if (pid == 0)
    {
		//printf("simon = %s\n", allcmd->cmd);
        ms_child(allcmd, fd, cmd);
        // free des trucs 
        exit(0);
    }
    else
	{
        ms_parent(allcmd, fd, cmd);
		// printf("lolo = %s\n", allcmd->cmd);
	}
	return (0);
}