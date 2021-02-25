#include "../minishell.h"

int		ms_which_builtin(t_cmd *cmd, t_allcmd *allcmd)
{
	//int		ret;
	char	*builtin;
	int		builtin_len;

	//ret = 0;
	builtin_len = 0;
	//cmd->builtinflag = NULL;
	// builtin = cmd->liste->first->cmd;
	builtin = allcmd->cmd;
	printf("builtin = %s\n", allcmd->cmd);
	builtin_len = ft_strlen(builtin);
	// printf("builtin_len = %d\n", builtin_len);
	// if (ft_strncmp("echo", builtin, (builtin_len + 1)) == 0)
	// {
	// 	ms_echo(cmd, allcmd);
	// }
	if (ft_strncmp("cd", builtin, (builtin_len + 1)) == 0)
		ms_cd(cmd, allcmd);
	else if (ft_strncmp("pwd", builtin, (builtin_len + 1)) == 0)
		ms_pwd();
	else if (ft_strncmp("export", builtin, (builtin_len + 1)) == 0)
		ms_export(cmd, allcmd);
	else if (ft_strncmp("unset", builtin, (builtin_len + 1)) == 0)
		ms_unset(cmd, allcmd);
	else if (ft_strncmp("env", builtin, (builtin_len + 1)) == 0)
		ms_env(cmd);
	// // else if (ft_strncmp("exit", builtin, (builtin_len + 1)) == 0)
	// //	ms_exit();
	 else
		ms_execve(cmd, allcmd);
	return (0);
}

int    ms_builtins(t_cmd *cmd, t_allcmd *allcmd)
{
	//printf("cmd = %s\n", allcmd->cmd);
	if (allcmd->cmd != NULL)
    {
        ms_which_builtin(cmd, allcmd);
    }
	return (0);
}

