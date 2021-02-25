#include "../minishell.h"

int		ms_if_quotes(t_cmd *cmd)
{
	cmd->i++;
	cmd->index++;
	while (cmd->quoteflag != 0 && cmd->line[cmd->i] != '\0')
	{
		ms_quoteflag(cmd, cmd->line[cmd->i]);
		if (cmd->line[cmd->i] == 92) //si backslash, je saute un caractere (dont les quotes)
		{
			cmd->index++;
			cmd->i++;
		}
		cmd->index++;
		cmd->i++;
	}
	return (1);
}

int		ms_if_no_quotes(t_cmd *cmd)
{
	cmd->i++;
	cmd->index++;
	while (cmd->line[cmd->i] != ' ' && cmd->quoteflag == 0 && cmd->line[cmd->i] != '\0')
	{
		ms_quoteflag(cmd, cmd->line[cmd->i]);
		cmd->index++;
		cmd->i++;
	}
	return (1);
}

static void     ms_remove_backslash(t_cmd *cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(cmd->new_token = malloc(sizeof(char) * (ft_strlen(cmd->token) + 1))))
		exit(0);
	while(cmd->quotetab[i] != '\0')
	{
		if (cmd->quotetab[i] == '1')
			cmd->new_token[j++] = cmd->token[i++];
		else
		{
			if (cmd->token[i] == 92)
			{
				i++;
				if (cmd->token[i] == '\0')
				{
					break;
					//printf("ERROR : BACKSLASH ENDING\n");
					//ms_exit();
				}
			}
			cmd->new_token[j++] = cmd->token[i++];
		}
	}
	cmd->new_token[j] = '\0';

    ms_free_and_init(&cmd->token);
	cmd->token = strdup(cmd->new_token);
	ms_free_and_init(&cmd->new_token);
}

static void     ms_copying_tokens(t_cmd *cmd)
{
	cmd->quoteflag = 0;
	while (cmd->line[cmd->i] != '\0')
	{
		ms_quoteflag(cmd, cmd->line[cmd->i]);
		if (cmd->quoteflag == 0)
			ms_if_no_quotes(cmd);
		else 
			ms_if_quotes(cmd);
		if (cmd->line[cmd->i] == ' ')
			break;		
	}
	// printf("index = %d\n", cmd->index);
	cmd->token = strndup(cmd->line + cmd->i - cmd->index, cmd->index);
	// printf("token = %s\n", cmd->token);
	// printf("len = %zu\n", ft_strlen(cmd->token));
}

int		ms_get_next_token(t_cmd *cmd)
{
	cmd->quoteflag = 0;
	cmd->index = 0;
	while (cmd->line[cmd->i] == ' ')
		cmd->i++;
	ms_copying_tokens(cmd);
	ms_remove_quotes(cmd);
	ms_remove_backslash(cmd);
    ms_free_and_init(&cmd->quotetab);
	return (1);
}