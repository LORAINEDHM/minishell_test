#include "minishell.h"

int		ms_quoteflag(t_cmd *cmd, char c)
{
	if (c == '\'')
	{
		//printf("' founded\n");
		if (!(S_Q & cmd->quoteflag) && !(D_Q & cmd->quoteflag))
		{
			    cmd->quoteflag |= S_Q;
			//    printf("simple quote flag 1\n");
		}
		else
		{
			cmd->quoteflag &= 0b111111110;
		//	printf("simple quote flag 0\n");
		}
	}
	else if (c == '"')
	{
		//printf("\" founded\n");
		if (!(D_Q & cmd->quoteflag) && !(S_Q & cmd->quoteflag))
		{
			cmd->quoteflag |= D_Q;
		//	printf("double quote flag 1\n");
		}
		else
		{
			cmd->quoteflag &= 0b11111101;
		//	printf("double quote flag 0\n");
		}
	}
	//ms_check_quotes(cmd);
	return (1);
}
