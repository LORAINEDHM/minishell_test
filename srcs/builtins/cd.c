#include "../minishell.h"

void    ms_cd(t_cmd *cmd, t_allcmd *allcmd)
{
    char	buff1[PATH_MAX + 1];

    cmd->temp = allcmd->argl;
    while (cmd->temp)
    {
        getcwd(buff1, PATH_MAX + 1);
        ft_putstr(buff1);
        ft_putstr("\n1\n");
        if (chdir(cmd->temp->content) == -1)
            exit(0);
        cmd->cd = getcwd(buff1, PATH_MAX + 1);
        //getcwd(buff1, PATH_MAX + 1);
        ft_putstr(buff1);
        ft_putstr("\n2\n");
		cmd->temp = cmd->temp->previous;
    }
}