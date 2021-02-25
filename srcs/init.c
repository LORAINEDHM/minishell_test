#include "minishell.h"

static size_t	ms_nb_elem_char_array(char **arr)
{
	unsigned int    i;
	size_t          count;

	i = 0;
	count = 0;
	while (arr[i])
	{
    	count++;
        i++;
    }
	return (count);
}

void	ms_init_env_list(t_cmd *cmd, char *envp[])
{
	unsigned int    i;
	int				first_flag;

	first_flag = 0;
	if (!(cmd->env_first = malloc(sizeof(t_env))))
		exit(0);
	cmd->env_first = NULL;
	i = 0;
	while (envp[i])
	{
		if (!(cmd->new_env = malloc(sizeof(t_env))))
			exit(0);
		cmd->new_env->content = NULL;
		cmd->new_env->next = NULL;
		if (!(cmd->new_env->content = ft_strdup(envp[i++])))
			ms_exit();
		if (first_flag == 1)  // already 1 allcmd list filled
			cmd->new_env->next = cmd->env;
		else  // 1st allcmd list to fill
			first_flag = 1;
		//cmd->env->previous = NULL;
		cmd->new_env->previous = NULL;
		cmd->env = cmd->new_env;
	}
    cmd->env_first = cmd->env;
	cmd->g_envp_len = i;
}

// void    ms_init_envp(t_cmd *cmd, int ac, char *argv[], char *envp[])
// {
// 	unsigned int    i;

// 	(void)ac;
// 	(void)argv;
// 	g_envp = (char **)ft_calloc(ms_nb_elem_char_array(envp) ,sizeof(char *));
// 	i = 0;

// 	while (envp[i])
// 	{
// 		if (!(g_envp[i] = ft_strdup(envp[i])))
// 			ms_exit();
//         i++;
// 	}
//     g_envp[i] = NULL;
// 	cmd->g_envp_len = i;
//     return;
// }

void	ms_init_cmd(t_cmd *cmd)
{
	cmd->fd = -1;
	cmd->inputdata = NULL;
	cmd->line = NULL;
    cmd->rest = NULL;
	cmd->file_path = NULL;
	cmd->token = NULL;
	cmd->quotetab = NULL;
	cmd->new_token = NULL;
	cmd->tab = NULL;
	cmd->dir_ret = NULL;
}

// void    ms_init_envp(int ac, char *argv[], char *envp[])
// {
// 	unsigned int    i;

// 	(void)ac;
// 	(void)argv;
// 	t_envp	*temp;
// 	// g_envp->var
// 	temp = g_envpl;
// 	i = 0;
// 	if (envp[i])
// 	{
// 		g_envpl->var = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	while (envp[i])
// 	{
// 		temp->next = malloc(sizeof(char *));
// 		temp = temp->next;
// 		if (!(temp->var = ft_strdup(envp[i])))
// 			exit(EXIT_FAILURE);
//         i++;
// 	}
//     temp->next = NULL;
//     return;
// }

