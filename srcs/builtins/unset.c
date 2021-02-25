#include "../minishell.h"

static int     ms_unset_get_and_check_var_name(t_cmd *cmd)
{
    int		ret;

	cmd->content = NULL;
	ret = 0;
	cmd->index = 0;
	cmd->var_name = NULL;
	cmd->content = cmd->temp->content;
	if ((ret = ms_check_validy(cmd->content, &cmd->index)) >= -1)
	{
		if (ret >= 0)
			error_msg(UNSET_UNVALID_IDENTIFIER, cmd->content);
		return (-1);
	}
	else if (ret == -2)
	{
		if (!(cmd->var_name = ms_strndup(cmd->content, cmd->index)))
			exit(0);
		printf("var_name = %s\n", cmd->var_name);
		return(1);
	}
	return(0);
}

static void		ms_unset_from_env_list(t_cmd *cmd, char *var_name, char *var_str)
{
    if (ms_get_env_var(cmd, var_name) != NULL)
	{
		if (cmd->env->previous != NULL)
		{
			cmd->env->next->previous = cmd->env->previous->next;
			cmd->env->previous->next = cmd->env->next;
		}
		else
		{
			cmd->env->next->previous = NULL;
			cmd->env_first = cmd->env->next;
		}
		ms_free_and_init(&cmd->env->content);
		cmd->env->next = NULL;
	}
}


void    ms_unset(t_cmd *cmd, t_allcmd *allcmd)
{
    cmd->temp = allcmd->argl;
    while (cmd->temp)
    {
        if (ms_unset_get_and_check_var_name(cmd) == 1)
		{
            ms_unset_from_env_list(cmd, cmd->var_name, cmd->content);
			cmd->content = NULL;
			ms_free_and_init(&cmd->var_name);
			ms_env(cmd);    // A SUPPRIMER
		}
		cmd->temp = cmd->temp->previous;
    }
}