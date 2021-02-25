#include "minishell.h"


void	ms_initialise_liste(t_cmd *cmd)
{
	printf("hello 1 \n");
	//cmd->liste = NULL;
	cmd->liste->first = NULL;
	cmd->liste->last = NULL;
	printf("hello 2\n");
}

void	ms_initialise_new_lists(t_cmd *cmd)
{
	cmd->new_allcmd->inputf = NULL;
	cmd->new_allcmd->inputl = NULL;
	cmd->new_allcmd->outputf = NULL;
	cmd->new_allcmd->outputl = NULL;
	cmd->new_allcmd->doutputf = NULL;
	cmd->new_allcmd->doutputl = NULL;
	cmd->new_allcmd->argf = NULL;
	cmd->new_allcmd->argl = NULL;
	cmd->new_allcmd->cmd = NULL;
	cmd->new_allcmd->next = NULL;
}

void	ms_addfront_token(t_cmd *cmd, t_token **first, t_token **last)
{
	t_token	*new_token;

	printf("cmd->token 1= %s\n", cmd->token);
	new_token = malloc(sizeof(t_token));
	new_token->content = malloc(sizeof(char) * ft_strlen(cmd->token) + 1);

    new_token->content = ft_strcpy(new_token->content, cmd->token);
	ms_free_and_init(&cmd->token);
	if (*first != NULL)
	{
		(*first)->previous = new_token;
		new_token->next = *first;
		// new_token->next->previous = new_token;
	}
	else // means it's the first input
	{
		printf("coucocu \n");
		new_token->next = NULL;
		*last = new_token;
		printf("coucou2\n");
	}
	new_token->previous = NULL;
    *first = new_token;
}