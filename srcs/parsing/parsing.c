#include "../minishell.h"


int     ms_parsing_quotes(t_cmd *cmd)
{
    cmd->i = 0;
    cmd->quoteflag = 0;
    while (cmd->line[cmd->i] != '\0')
    {
        ms_quoteflag(cmd, cmd->line[cmd->i]);
        // char a = cmd->quoteflag;
    	// int i;
        // for (i = 0; i < 8; i++) {
        //  printf("%d", !!((a << i) & 0x80));
        // }
        // printf("\n");


		// if (S_Q & cmd->quoteflag)
		// 	cmd->i++;
		// else if (D_Q & cmd->quoteflag)
		// {
		// 	ms_dollar(cmd);
		// 	ms_backslash(cmd);
		// }
		// else if (!(S_Q & cmd->quoteflag) && !(D_Q & cmd->quoteflag))
		// {
		// 	printf("outside quotes\n");
		// }

		
        cmd->i++;
    }
    
    // char a = cmd->quoteflag;
    // int i;
    //     for (i = 0; i < 8; i++) {
    //      printf("%d", !!((a << i) & 0x80));
    //     }
    //     printf("\n");
    return (1);
}

int    ms_parsing(t_cmd *cmd)
{
	t_var	var;
	// t_slash	slash;
	t_pipe pipe;

	// //int		i; // lignes
	// int		j; // colonnes
 	ms_sep_semicolon(cmd);
	ms_dollar(cmd, &var);
    printf("cmd line = %s\n\n", cmd->line);
	ms_pipe_split(cmd, &pipe);
	ms_split_in_tokens(cmd);

	//printf("cmd line = %s\n\n", cmd->line);
	// j = 0;gi
	// while (j < pipe.nb_str) 
	// {
	// 	printf("tab[j] = %s\n", cmd->tab[j]);
	// 	j++;
	// }
	// j = 0;
	// while (cmd->tab[j] != NULL)
	// {
	// 	cmd->line = NULL;
	// 	cmd->line = cmd->tab[j];
	// 	cmd->tab[j] = NULL;
	// 	//printf("cmd->line = %s\n", cmd->line);
	//  	ms_backslash(cmd, &slash);
	// 	cmd->tab[j] = cmd->line;
	// 	j++;
	// }
	// // j = 0;
	// // while (cmd->tab[j] != NULL) 
	// // {
	// // 	printf("tab[j] = %s\n", cmd->tab[j]);
	// // 	j++;
	// // }
	// //ms_free_and_init(cmd->line);
	return (1);
}
