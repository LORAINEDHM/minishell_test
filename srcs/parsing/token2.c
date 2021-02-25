#include "../minishell.h"

void    ms_token_to_struct(t_cmd *cmd)
{   
	if (CMD & cmd->tokenflag)
	{
		//printf("cmd->allcmd->cmd = %s\n", cmd->allcmd->cmd);
		cmd->allcmd->cmd = strdup(cmd->token);
	}
	else
	{
		if (INPUT & cmd->tokenflag)
			ms_addfront_token(cmd, &cmd->allcmd->inputf, &cmd->allcmd->inputl);
		else if (OUTPUT & cmd->tokenflag)
		{
			ms_addfront_token(cmd, &cmd->allcmd->outputf, &cmd->allcmd->outputl);
			cmd->allcmd->lastoutputtype = S_CHEVRON;

		}
		else if (DOUTPUT & cmd->tokenflag)
		{
			ms_addfront_token(cmd, &cmd->allcmd->doutputf, &cmd->allcmd->doutputl);
			cmd->allcmd->lastoutputtype = D_CHEVRON;
		}
		else if (ARG & cmd->tokenflag)
			ms_addfront_token(cmd, &cmd->allcmd->argf, &cmd->allcmd->argl);
	}
}

int		ms_redirection_token(t_cmd *cmd)
{
	cmd->rdirflag = 0;
	if (cmd->line[cmd->i] == '<')
	{
		//printf ("input\n");
		cmd->tokenflag |= INPUT;
	}
	else if (cmd->line[cmd->i] == '>')
	{
		if (cmd->line[cmd->i+1] == '>')
		{
			cmd->i++;
			//printf ("double output\n");
			cmd->tokenflag |= DOUTPUT;
		}
		else
		{
			//printf("simple output\n");
			cmd->tokenflag |= OUTPUT;
		}
	}
	return (0);
}
