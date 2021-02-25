#include "../minishell.h"

void    ms_handle_o_s_redirections(t_cmd *cmd, t_allcmd *allcmd)
{
    int         fd;
    char        *path;
    char        *buff[PATH_MAX];
    t_token     *temp;

    //  printf("test\n");
    temp = allcmd->outputf;
    //  printf("test3\n");
    // printf("content %s\n", temp->content);
    if (temp != NULL)
    {
        path = ms_return_path(cmd->cd, temp->content);
		fd = open(path, O_WRONLY | O_TRUNC);
        // printf("fd c'est %d\n", fd);
		free(path);
        temp = NULL;
	}
    if (cmd->allcmd->lastoutputtype == S_CHEVRON)
    {
    if (cmd->fd == -1)
		cmd->fd = dup(1);
        dup2(fd, 1); // ecrire sur le 1 va écrire dans le fd
	    close(fd); // on peut fermer le fd du coup car 1 sera le fd
    }
}

void    ms_handle_o_d_redirections(t_cmd *cmd, t_allcmd *allcmd)
{
    int         fd;
    char        *path;
    char        *buff[PATH_MAX];
    t_token     *temp;

//  printf("test\n");
    temp = allcmd->doutputf;
//  printf("test2\n");
    if (temp != NULL)
    {
        path = ms_return_path(cmd->cd, temp->content);
		fd = open(path, O_WRONLY | O_APPEND);
		free(path);
        temp = NULL;
	}
    if (cmd->allcmd->lastoutputtype == D_CHEVRON)
    {
        if (cmd->fd == -1)
            cmd->fd = dup(1);
        dup2(fd, 1); // ecrire sur le 1 va écrire dans le fd
        close(fd); // on peut fermer le fd du coup car 1 sera le fd
    }
}



void    ms_handle_i_redirections(t_cmd *cmd, t_allcmd *allcmd)
{
    int     fd;
    char    *path;
    char    buff[2];
    char    *temp;
    int     ret;

    cmd->temp = allcmd->inputf;
    // printf("test\n");
    while (cmd->temp != NULL)
    {
        path = ms_return_path(cmd->cd, cmd->temp->content);
        printf("path %s \n", path);
        fd = open(path, O_RDONLY);
        free(cmd->inputdata);
        cmd->inputdata = NULL;
        while ((ret = read(fd, buff, 1)) > 0)
        {
            // printf("buff %s\n", buff);
            buff[ret] = '\0';
            temp = cmd->inputdata;
            cmd->inputdata = ft_strjoin(temp, buff);
            if (temp != NULL)
                free (temp);
        }
        cmd->temp = cmd->temp->next;
        close(fd);
    }
}