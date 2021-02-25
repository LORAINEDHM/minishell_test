#include "../minishell.h"

static void	ms_init(t_cmd *cmd)
{
	cmd->i = 0;
	cmd->quoteflag = 0;
}

static void	ms_check_backslash(t_cmd *cmd)
{
	ms_quoteflag(cmd, cmd->line[cmd->i]);
	while (cmd->line[cmd->i] == 92 && !(S_Q & cmd->quoteflag))
	{
		cmd->i += 2;
		ms_quoteflag(cmd, cmd->line[cmd->i]);
	}
}


void		ms_sep_semicolon(t_cmd *cmd)
{
    ms_init(cmd);
	// printf("cmd line = %s\n\n", cmd->line);
	while (1)
	{
		if (cmd->line[cmd->i] != '\0') // quand c'est ';'
		{
			ms_check_backslash(cmd);
			if (cmd->line[cmd->i] == ';' && cmd->quoteflag == 0)
			{
				cmd->line[cmd->i] = 0;
				ms_free_and_init(&cmd->rest);
				if(cmd->line[cmd->i + 1] != '\0') // pour les fin de gnl en ';'
				{
					if (!(cmd->rest = ft_strdup(cmd->line + (cmd->i + 1))))
						exit(0);
				}
				break;
			}
		}
		else // derniere commande = fin de la ligne gnl
		{
			ms_free_and_init(&cmd->rest);
			break;
		}
		cmd->i++;
	}
}