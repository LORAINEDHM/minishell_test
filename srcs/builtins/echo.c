#include "../minishell.h"

static void	ms_putstr_token_echo(t_cmd *cmd)
{
	while (cmd->temp)
	{
		ft_putstr(cmd->temp->content);
		cmd->temp = cmd->temp->previous;
		if (cmd->temp != NULL)
			ft_putstr(" ");
	}
	if (cmd->n_flag == 0)
		ft_putstr("\n");
	return;
}


static int		ms_check_n_option(t_cmd *cmd)
{
	int i;

	if (ft_strncmp("-n", cmd->temp->content, 2) == 0)
	{
		i = 2;
		while (cmd->temp->content[i] != '\0')  // i check if -nnnnnnn
		{
			if (cmd->temp->content[i] == 'n')
				i++;
			else
				break;
		}
		if (cmd->temp->content[i] == '\0')
		{
			cmd->n_flag = 1;
			return (1);
		}
	}
	return (0);
}

static void	ms_parsing_echo(t_cmd *cmd, t_allcmd *allcmd)
{
	// cmd->allcmd = cmd->liste->first;
	cmd->temp = allcmd->argl;
	cmd->n_flag = 0;
	while (cmd->temp && (ms_check_n_option(cmd) == 1))  // skip tous les premiers -n
		cmd->temp = cmd->temp->previous;
	if (cmd->n_flag == 0)
		// printf("no -n option \n");
	return;
}

int		ms_echo(t_cmd *cmd, t_allcmd *allcmd)
{
	ms_parsing_echo(cmd, allcmd);
	ms_putstr_token_echo(cmd);
	return (0);

}