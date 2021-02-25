#include "../minishell.h"



static int		ms_check_if_slash(t_cmd *cmd)
{
    int i;

    i = 0;
    cmd->i = 0;
    while (cmd->line[cmd->i] != '\0')
    {
		ms_quoteflag(cmd, cmd->line[cmd->i]);
        if (cmd->line[cmd->i] == 92 && !(S_Q & cmd->quoteflag) 
            && cmd->line[cmd->i+1] != '\0')
        {
            if (!(D_Q & cmd->quoteflag)
                || ((D_Q & cmd->quoteflag) && cmd->line[cmd->i+1] == '$')) // si $ entre DQ, il faut faire dispraitre le \'
            {
                i++;
                cmd->i++;
            }
        }
        cmd->i++;
    }
    return (i);
}

static int     ms_copy_newline_slash(t_cmd *cmd, t_slash *slash)
{
    int i;

    i = 0;
    cmd->i = 0;
    cmd->quoteflag = 0;
    slash->newline = NULL;
    slash->newline = (malloc(sizeof(char) * (slash->line_length - slash->number + 1)));
    while (cmd->line[cmd->i] != '\0')
    {
        ms_quoteflag(cmd, cmd->line[cmd->i]);
        if (cmd->line[cmd->i] == 92 && !(S_Q & cmd->quoteflag) 
            && cmd->line[cmd->i+1] != '\0')
        {
            if (!(D_Q & cmd->quoteflag)
                || ((D_Q & cmd->quoteflag) && cmd->line[cmd->i+1] == '$'))
                cmd->i++;  // on incremente pour sauter le \'
        }
        slash->newline[i] = cmd->line[cmd->i];
        if (cmd->line[cmd->i] == '\0')
            break;
        cmd->i++;
        i++;
    }
    slash->newline[i] = '\0';
    return (1);
}

int    ms_backslash(t_cmd *cmd, t_slash *slash)
{
    cmd->i = 0;
	cmd->quoteflag = 0;
    slash->line_length = ft_strlen(cmd->line);
    //printf("line_length = %d\n", slash->line_length);
    slash->number = ms_check_if_slash(cmd); //return nb of slash
    //printf("slash->number = %d\n", slash->number);
    if (slash->number > 0)
    {
        ms_copy_newline_slash(cmd, slash);
        free(cmd->line);
		cmd->line = NULL;
        cmd->line = ft_strdup(slash->newline);
		free(slash->newline);
		slash->newline = NULL;
    }
    printf("slash line = %s\n", cmd->line);
	return (1);
}