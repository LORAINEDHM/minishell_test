#include "../minishell.h"

void    ms_env(t_cmd *cmd)
{
    cmd->env = cmd->env_first;
    while(cmd->env)
    {
        ft_putstr(cmd->env->content);
        ft_putstr("\n");
        //printf("cmd->env->content = %s\n", cmd->env->content);
        cmd->env = cmd->env->next;
    }
}