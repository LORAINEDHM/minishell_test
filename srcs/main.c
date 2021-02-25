#include "minishell.h"

int     main(int ac, char *argv[], char *envp[])
{
    t_cmd	*cmd;
    // t_liste *liste;


    // while (1)
	// {
        cmd = malloc(sizeof(t_cmd));
        ms_init_cmd(cmd);
        ms_init_env_list(cmd, envp);
        //print_list(cmd);
        ms_env(cmd);   // A SUPPRIMER
	   // ms_init_envp(cmd, ac, argv, envp);
        while (1)
        {
            ms_display_prompt_message(cmd);
            get_next_line(1, &cmd->rest);
            if(cmd->rest[0] == '\0')
                cmd->rest = NULL;
        // ms_init_memory();
        // execve(cmd.file_path, NULL, NULL); // voir pour corriger ca
            while (NULL != cmd->rest)  // while to split line into commands (when a comma is found)
            {
                //printf("cmd line = %s\n\n", cmd->rest);
                cmd->line = ft_strdup(cmd->rest);
		        //printf("cmd line = %s\n\n", cmd->line);
                ms_parsing(cmd);
                // cmd->allcmd = cmd->liste->first; // il faudra que dans cmd->allcmd il y aura tjrs le bon
                cmd->allcmd = cmd->liste->first;
                // printf("cmd    %s\n", cmd ->liste->first->cmd);
                ms_fork(cmd->liste->first, cmd);
                // printf("brol\n");
                // printf("brol\n%p\n", cmd->liste);
                // printf("brol\n");
                printf("cmd    %s\n", cmd ->liste->first->cmd);
                // ms_redirections(cmd, cmd->liste->first);// il faudra que dans (cmd->allcmd !!!)il y aura tjrs le bon
                
               
             
    //             // ms_free_all_lists(cmd);
                //printf("coucou\n");
                //printf("cmd->liste->first->cmd = %p\n", cmd->liste->first);
               // printf("cmd->liste->first->cmd = %s\n", cmd->liste->first->cmd);
                //printf("cmd->liste->first->cmd\n", cmd->liste->first->cmd);
			   //ms_builtins(cmd, cmd->liste->first);
	// 		    // ms_path(cmd, "ls");
    //             //ms_free_and_init(cmd->line);
                ms_free_and_init(&cmd->line);
                // cmd->rest = NULL
// ms_free_doubletab(cmd->tab, cmd->pipe_nb); 
                ms_free_all_lists(cmd); 
            }
            // ms_free_and_init(cmd->rest);
    //         // char a = ms_comma(&cmd);
    //         // int i;
    //         // for (i = 0; i < 8; i++) {
    //         //  printf("%d", !!((a << i) & 0x80));
    //         // }
    //         // printf("\n");
            // ms_free_doubletab(g_envp, 100);
           //break;
        }
        // ms_free_doubletab(g_envp, cmd->g_envp_len - 1);
        free(cmd);
       // ms_exit();
	   // return (0);
    // }
    // system("leaks ./minishell");
    return (0);
}
