#include "../minishell.h"

static int		ms_file_exists(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
    // printf("fd lol %d", fd);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

char	*ms_return_path(char *cd, char *filename)
{
	char	*tmp;
    char    *path;

	tmp = ft_strjoin(cd, "/"); // check pour malloc
	path = ft_strjoin(tmp, filename); // check pour malloc
	free(tmp);
	return (path);
}

static void ms_input_redirection(t_cmd *cmd, t_allcmd *allcmd)
{
    // printf("ricrac \n");
    t_token *temp;
    char    *buff[PATH_MAX];
    // char    *str;
    char    *path;

    temp = allcmd->inputf;
    // printf("shiiiit \n");
    while (temp != NULL)
	{
        if (temp->content == NULL)
            exit(EXIT_FAILURE); //message d'erreur bash: syntax error near unexpected token
        // str = ft_strjoin(getcwd(buff, PATH_MAX),'/');
        // path = ft_strjoin(str, temp->content);
        // free(str);
        path = ms_return_path(cmd->cd, temp->content);
        // printf("path %s \n", path);
        if (ms_file_exists(path) != 0)
            exit(EXIT_FAILURE); //message d'erreur (bash: <name_of_file>: No such file or directory)
        free (path);
        temp = temp->next;
    }
    // printf("done \n");

}

static void ms_output_redirection(t_cmd *cmd, t_token *output)
{
    // t_token *temp;
    char    *buff[PATH_MAX];
    char    *path;
    int     fd;

    // temp = output;
    while (output != NULL)
	{
        // printf("start \n");
        if (output->content == NULL)
            exit(EXIT_FAILURE); //message d'erreur (bash: <name_of_file>: No such file or directory)
        path = ms_return_path(cmd->cd, output->content);
        // printf("path %s \n", path);
        if (ms_file_exists(path) != 0)
            fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH); // permission 664
            // exit(EXIT_FAILURE); //message d'erreur (bash: <name_of_file>: No such file or directory)
        // printf("fd %d", fd);
        free (path);
        output = output->next;
        // printf("t n %s \n", temp->content);
        if (fd < 0)
            exit(EXIT_FAILURE); // erreur de open
        close (fd);
        //  printf("done \n");
    }
}

// static void ms_d_output_redirection(t_token *outputf)
// {
//     t_token temp;
//     char    *buff[PATH_MAX];
//     char    *path;
//     int     fd;

//     temp = allcmd->doutput;
//     while (temp != NULL)
// 	{
//         if (temp->content == NULL)
//             exit(EXIT_FAILURE); //message d'erreur (bash: <name_of_file>: No such file or directory)
//         path = ms_return_path(getcwd(buff, PATH_MAX), temp->content);
//         if (ms_file_exists(path) != 0)
//             exit(EXIT_FAILURE); //message d'erreur (bash: <name_of_file>: No such file or directory)
//         fd = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
//         free (path);
//         temp = temp->next;
//         if (fd < 0)
//             exit(EXIT_FAILURE); // erreur de open
//         close (fd);
//     }
// 	return (0);
// }

static int  ms_check_redirections(t_cmd *cmd, t_allcmd *allcmd)
{
    ms_input_redirection(cmd, allcmd);
    ms_output_redirection(cmd, allcmd->outputf);
    ms_output_redirection(cmd, allcmd->doutputf);
    return (0);
}


int			ms_redirections(t_cmd *cmd, t_allcmd *allcmd)
{
    cmd->cd = strdup("/home/simon/Desktop/minishell"); // marche pas quand ca commence avec chemin relatif!
    ms_check_redirections(cmd, allcmd);
    // if (allcmd->lastoutputtype == S_CHEVRON)
    //     ms_handle_o_s_redirections(cmd, allcmd);
    // if (allcmd->lastoutputtype == D_CHEVRON)
    //     ms_handle_o_d_redirections(cmd, allcmd);
    // ms_handle_i_redirections(cmd, allcmd);	
	return (0);
}