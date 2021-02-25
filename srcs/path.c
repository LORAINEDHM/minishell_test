#include "minishell.h"

//    https://pub.phyks.me/sdz/sdz/arcourir-les-dossiers-avec-dirent-h.html
//    http://manpagesfr.free.fr/man/man3/readdir.3.html

void		ms_path(t_cmd *cmd, char *bash_cmd, t_allcmd *allcmd) 
{
    char    **paths;
    int i;
    int ret;

    paths = ft_split(ms_get_env_var(cmd, "PATH"), ':'); // stocke tout le chemin de path
    i = 0;
    ret = 0;
    while (paths[i])
    {
        // printf("env %s\n", paths[i]);
        ret = ms_test_path(cmd, paths[i], bash_cmd, allcmd);
        closedir(cmd->dir_ret);
        if (ret == 1)
			return;  // means bash_cmd is found into the directory path[i]
        i++; 
    }
    // ms_free_and_init_dtab(paths);
	error_msg(CMD_NOT_FOUND, bash_cmd);
	exit(EXIT_FAILURE); // temp
	//return;
}

char    *ms_join_path(char *path_dir, char *bash_cmd)
{
    char *new_path;
    char *file_path;

    new_path = NULL;
    file_path = NULL;
    if (((new_path = ft_strjoin(path_dir, "/")) == NULL)
    	|| ((file_path = ft_strjoin(new_path, bash_cmd)) == NULL))
		exit(EXIT_FAILURE);
	free(new_path);
	return(file_path);
}


int		ms_test_path(t_cmd *cmd, char *path_dir, char *bash_cmd, t_allcmd *allcmd) 
{
    struct	dirent* dirent;
    // int		i;
    int		ret;

    // i = 0;
    ret = 0;
    cmd->dir_ret = NULL;
    cmd->dir_ret = opendir(path_dir);
    if (cmd->dir_ret != NULL)
    {
        // printf("Directory is opened!\n");   // effacer a la fin
    }
    else
    {
        printf("Unable to read directory\n");  // effacer a la fin
        exit(EXIT_FAILURE); // changer ca
    }
    while (1)
    {
        dirent = NULL;
        ret = 0;
        if ((dirent = readdir(cmd->dir_ret)) == NULL)
			return (0);
        //printf("d_name = %s\n", dirent->d_name);
        ret = (ft_strncmp(dirent->d_name, bash_cmd, (ft_strlen(bash_cmd)+1)));
        if (ret == 0) // means the cmd is found
        {
            // printf ("cmd found in the directory !!! ");   // effacer a la fin
            if ((allcmd->cmdpath = ms_join_path(path_dir, bash_cmd)) == NULL) // adding "/bash_cmd" to path_dir
				exit(EXIT_FAILURE);
			// printf("file_path = %s\n", allcmd->cmdpath);
	        // closedir(cmd->dir_ret);  // fermer le dossier paths[i] qui a ete ouvert dans ms_test_path
            return (1);
        }
    }
	// closedir(cmd->dir_ret);  // fermer le dossier paths[i] qui a ete ouvert dans ms_test_path
    return (0);
}