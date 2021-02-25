
#include "../minishell.h"

static void            ms_init(t_cmd *cmd, t_pipe *pipe)
{
    cmd->i = 0;
	cmd->j = 0;
    cmd->quoteflag = 0;
	cmd->pipe_nb = 0;
    pipe->split_flag = 0;
	pipe->nb_str = 0;
    pipe->index = 0;
    cmd->tab = NULL;
}

char		*ms_strndup(const char *src, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = NULL;
	if (!(ptr = (char*)malloc(sizeof(char) * n + 1)))
		return (NULL);
	i = 0;
	while (src[i] != '\0' && i < n)
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static int		ms_nb_strings(t_cmd *cmd, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd->line[i] != c)
		j = 1;
	while (cmd->line[i] != '\0')
	{
        ms_quoteflag(cmd, cmd->line[i]);
        while (cmd->line[i] == 92)
		{
		    i += 2;
			ms_quoteflag(cmd, cmd->line[i]);
        }
        if (cmd->line[i] == c && !(S_Q & cmd->quoteflag) && !(D_Q & cmd->quoteflag))
			j++;
        i++;
	}
	// printf("Number of total string cut in by pipes %d\n", j);
    cmd->quoteflag = 0;
	return (j);
}

static void			ms_end_of_line(t_cmd *cmd, t_pipe *pipe)
{
    if (cmd->line[cmd->i] == '|' || cmd->line[cmd->i + 1] == '\0')  // A CORRIGER PAR UN IF UNE FOIS QU ON SAIT COMMENT FAIRE AVEC LES | D AFFILE
	{
        //printf("end_of_line\n");
        if (cmd->line[cmd->i] == '|')
        {
            //printf("| found\n");
            //printf("quoteflag = %d\n", cmd->quoteflag);
			if (!(S_Q & cmd->quoteflag) && (!(D_Q & cmd->quoteflag)))
            {
				//printf("NEED TO SPLIT !");
                pipe->split_flag = 1;
                //printf("final | pipe->index = %d\n", pipe->index);
                if (!(cmd->tab[cmd->j++] = ms_strndup(cmd->line + cmd->i - pipe->index, pipe->index)))
                    exit(0);
            }
        }
        else
        {
            //printf("'0 found\n");
            if (!(cmd->tab[cmd->j++] = ms_strndup(cmd->line + cmd->i - pipe->index, pipe->index + 1)))
				exit(0);
        }
    }
}

static void	ms_check_backslash(t_cmd *cmd, t_pipe *pipe)
{
	ms_quoteflag(cmd, cmd->line[cmd->i]);
	while (cmd->line[cmd->i] == 92 && !(S_Q & cmd->quoteflag))
	{
		cmd->i += 2;
		pipe->index +=2;
		ms_quoteflag(cmd, cmd->line[cmd->i]);
	}
}

char			**ms_pipe_split(t_cmd *cmd, t_pipe *pipe)
{
    ms_init(cmd, pipe);
	//
    pipe->nb_str = ms_nb_strings(cmd, '|');
	cmd->pipe_nb = pipe->nb_str;
	// printf("sizeof %lu\n",sizeof(*(cmd->tab)));
	if (!(cmd->tab = malloc(sizeof(*cmd->tab) * (pipe->nb_str + 1))))
		exit(0);
	while (cmd->line[cmd->i] != '\0' && cmd->j < pipe->nb_str)
	{
       // printf("pipe->index = %d\n", pipe->index);
		if (pipe->split_flag == 1) 
        {
            pipe->index = 0;
            cmd->quoteflag = 0;
        }
        pipe->split_flag = 0;
		ms_check_backslash(cmd ,pipe);
        ms_end_of_line(cmd, pipe);
        pipe->index++;
		cmd->i++;
	}
	cmd->tab[cmd->j] = NULL;
	// printf("hello 4\n");
	// int i =0;
	// while (cmd->tab[i])
	// {
	// 	// printf("cmd->tab[%d] %s\n", i, cmd->tab[i]);
	// 	i++;
	// }
	return (cmd->tab);
}