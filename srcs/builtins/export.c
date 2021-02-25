#include "../minishell.h"

int     ms_check_validy(char *content, int *index)
{
    int i;

    if (content == NULL)
        return (-1);
	if (ft_isdigit(content[0]))
		return (0);
    i = 0;
    while (content[i] != '\0' && content[i] != '=')
    {
        if (!(ft_isalnum(content[i])) && content[i] != '_')
		{
			printf("unvalid char in var name\n");
            return (0);
		}
        i++;
    }
    if (content[i] == '=')
        return(*index = i);
    else
	{
		*index = i;
        return (-2);
	}
}

static void		ms_addfront_var_env(t_cmd *cmd, char *var_str)
{
	if (!(cmd->new_env = malloc(sizeof(t_env))))
			exit(0);
	cmd->new_env->content = NULL;
	cmd->new_env->next = NULL;
	if (!(cmd->new_env->content = ft_strdup(var_str)))
		ms_exit();
	cmd->new_env->next = cmd->env;
	cmd->env = cmd->new_env;
	cmd->env_first = cmd->env;
}

static void		ms_add_to_env_list(t_cmd *cmd, char *var_name, char *var_str)
{
	if (ms_get_env_var(cmd, var_name) != NULL)
	{
		ms_free_and_init(&cmd->env->content);
		if (!(cmd->env->content = ft_strdup(var_str)))
			exit(0);
	}
	else
	{
		printf("doesn't already exist\n");
		cmd->env = cmd->env_first;
		ms_addfront_var_env(cmd, var_str);
	}
	
}

static int     ms_export_get_and_check_var_name(t_cmd *cmd)
{
   // int		index;

	cmd->content = NULL;
	cmd->index = 0;
	cmd->var_name = NULL;
	cmd->content = cmd->temp->content;
	if (ms_check_validy(cmd->content, &cmd->index) <= 0)
	{
		if (cmd->index == 0)
			error_msg(EXPORT_UNVALID_IDENTIFIER, cmd->content);
		return (-1);
	}
	else
	{
		if (!(cmd->var_name = ms_strndup(cmd->content, cmd->index)))
			exit(0);
		printf("var_name = %s\n", cmd->var_name);
		return(1);
	}
}

void    ms_export(t_cmd *cmd, t_allcmd *allcmd)
{
    cmd->temp = allcmd->argl;
    while (cmd->temp)
    {
        if (ms_export_get_and_check_var_name(cmd) == 1)
		{
			ms_add_to_env_list(cmd, cmd->var_name, cmd->content);
			cmd->content = NULL;
			ms_free_and_init(&cmd->var_name);
			ms_env(cmd);   // A SUPPRIMER
		}
		cmd->temp = cmd->temp->previous;
    }
}