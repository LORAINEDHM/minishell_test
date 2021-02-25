#include "../minishell.h"

static int		ms_count_arg(t_token *token)
{
	t_token *temp;
	int i;

	i = 0;
	temp = token;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

static char		**ms_arg_to_dtab(t_allcmd *allcmd)
{
	char **tab;
	t_token *temp;
	int i;

	i = 0;
	if (!(tab = malloc(sizeof(char *)*(ms_count_arg(allcmd->argf) + 2))))
		exit(0);
	tab[i] = allcmd->cmdpath;
	// printf("tab[i] = %s\n", tab[i]);
	i++;
	temp = allcmd->argf;
	while (temp != NULL)
	{
		tab[i] = temp->content;
		// printf("tab[i] = %s\n", tab[i]);
		i++;
		temp = temp->next;
	}
	// printf("done done done\n");
	tab[i] = NULL;
	return (tab);
}

static char		**ms_env_list_to_doubletab(t_cmd *cmd)
{
	unsigned int i;

	i = 0;
	cmd->env = cmd->env_first;
	while(cmd->env)
	{
		i++;
		cmd->env = cmd->env->next;
	}
	g_envp = (char **)ft_calloc(i + 1, sizeof(char *));
 	i = 0;
	cmd->env = cmd->env_first;
 	while (cmd->env)
 	{
		if (!(g_envp[i] = ft_strdup(cmd->env->content)))
 			ms_exit();
		i++;
		cmd->env = cmd->env->next;
 	}
	return(g_envp);
}

int			ms_execve(t_cmd *cmd, t_allcmd *allcmd)
{
	int		fd[2];
	char	**tab;
	int	j =0;
    // t_cmd	cmd;

	ms_path(cmd, allcmd->cmd, allcmd);
	// printf("path = %s\n", allcmd->cmdpath);
	pipe(fd);
	if ((g_pid = fork()) == 0)
	{
		if (cmd->inputdata != NULL) 
			dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);

		// ms_list_to_doubletab(cmd);
		// i = 0;
		// while (g_envp[i])
		// {
		// 	printf("g_envp[i] = %s\n", g_envp[i]);
		// 	i++;
		// }
		// AJOUTER FONCTION QUI CONVERTIT ENV_LIST EN DTAB G_ENVP EN 3EME PARAMETRE DE LA FONCTION EXECVE
		execve(allcmd->cmdpath, ms_arg_to_dtab(allcmd), ms_env_list_to_doubletab(cmd));
		exit(1);
	}
	// printf("path  input data= %s\n", cmd->inputdata);
	if (cmd->inputdata != NULL)
		ft_putstr_fd(cmd->inputdata, fd[1]);
	close(fd[0]);
	close(fd[1]);
	wait(&g_pid);
	
	g_pid = -1;
	return (0);
}

