#include "../minishell.h"

void	ms_record_quotef(t_cmd *cmd)
{
	ms_quoteflag(cmd, cmd->token[cmd->k]);
	if (S_Q & cmd->quoteflag)
		cmd->quotef = '1';
	else if (D_Q & cmd->quoteflag)
		cmd->quotef = '2';
	else
		cmd->quotef = '0';
}

void     ms_remove_quotes(t_cmd *cmd)
{
	cmd->k = 0;
	cmd->j = 0;
	cmd->quoteflag = 0;
	cmd->quotef = '0'; 
	cmd->token_len = ft_strlen(cmd->token);
	//printf("token_len = %d\n", cmd->token_len);
	if ((!(cmd->new_token = malloc(sizeof(char) * (cmd->token_len + 1))))
		|| (!(cmd->quotetab = malloc(sizeof(char) * (cmd->token_len + 1)))))
		exit(0);
	while (cmd->token[cmd->k] != '\0')
	{
		ms_record_quotef(cmd);
		if (cmd->token[cmd->k] == 34 || cmd->token[cmd->k] == 39)
		{
			cmd->k++;
			if (cmd->token[cmd->k] == '\0')
				break;
		}
		if (cmd->token[cmd->k] == 92)
		{
			cmd->new_token[cmd->j] = cmd->token[cmd->k];
			cmd->quotetab[cmd->j] = cmd->quotef;
			if (cmd->token[cmd->k+1] != '\0')
			{
				cmd->k++;
				cmd->j++;
                ms_quoteflag(cmd, cmd->token[cmd->k]);
			}
		}
        if (!(cmd->token[cmd->k] == 39 && cmd->quoteflag == 0))
        {
		    cmd->new_token[cmd->j] = cmd->token[cmd->k];
		    cmd->quotetab[cmd->j] = cmd->quotef;
		    cmd->k++;
		    cmd->j++;
        }
        else
        {
            break;
        }   
	}
	cmd->new_token[cmd->j] = '\0';
	cmd->quotetab[cmd->j] = '\0';
	ms_free_and_init(&cmd->token);
	cmd->token = strdup(cmd->new_token);
  //  printf("token quotes = %s\n", cmd->token);
	ms_free_and_init(&cmd->new_token);
}

