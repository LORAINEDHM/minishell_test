#include "minishell.h"

// char	*ms_get_env_var_old(char *envv)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	tmp = ft_strjoin(envv, "=");
// 	while (g_envp[i])
// 	{
// 		if (ft_strncmp(g_envp[i], tmp, strlen(tmp)) == 0)
// 		{
// 			free(tmp);
// 			return (ft_strchr(g_envp[i], '=') + 1);
// 		}
//         i++;
// 	}
// 	free(tmp);
// 	return (NULL);
// }

char	*ms_get_env_var(t_cmd *cmd, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	
	cmd->env = cmd->env_first;
	while (cmd->env)
	{
		if (ft_strncmp(cmd->env->content, tmp, strlen(tmp)) == 0)
		{
			free(tmp);
			return (ft_strchr(cmd->env->content, '=') + 1);
		}
        cmd->env = cmd->env->next;
	}
	free(tmp);
	return (NULL);
}


int		ms_check_cmd_validity(t_cmd *cmd, char *envv)
{
	// int i;

	// i = 0;
	cmd->i += ft_strlen(envv);
	printf("i = %d\n", cmd->i);
	while (cmd->line[cmd->i] == ' ')
		cmd->i++;
	if (cmd->line[cmd->i] != '\0')
	{
		printf("unvalid command\n");
		return (-1);
	}
	else
		return (1);
}