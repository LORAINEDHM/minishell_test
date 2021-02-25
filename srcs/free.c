#include "minishell.h"

void	ms_free_char_array(char **arr) 
{
	int i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
        arr[i] = NULL;
        i++;
	}
	free(arr);
	arr = NULL;
}

void	ms_free_tokenlist(t_token **token)
{
	while (*token != NULL)
	{
		if ((*token)->content != NULL)
		{
			ms_free_and_init(&(*token)->content);
		}
		if ((*token)->next != NULL)
		{
			*token = (*token)->next;
			ms_free_and_init_token(&(*token)->previous);
		}
	}
	ms_free_and_init_token(&(*token));
}

void	ms_free_all_lists(t_cmd *cmd)
{
	t_allcmd *temp;

	// printf("hello\n");
	// temp = cmd->liste->first->next;
	// temp = cmd->liste->first;
	// printf("hello1\n");

	cmd->allcmd = cmd->liste->first;
	// printf("hello2\n");
	while (cmd->allcmd != NULL)
	{
		// if (cmd->allcmd->cmd != NULL)
		// 	ms_free_and_init(&cmd->allcmd->cmd);
		// if (cmd->allcmd->inputf != NULL)
		// 	ms_free_tokenlist(&cmd->allcmd->inputf);
		// if (cmd->allcmd->outputf != NULL)
		// 	ms_free_tokenlist(&cmd->allcmd->outputf);
		// if (cmd->allcmd->doutputf != NULL)
		// 	ms_free_tokenlist(&cmd->allcmd->doutputf);
		// if (cmd->allcmd->argf != NULL)
		// 	ms_free_tokenlist(&cmd->allcmd->argf);
		cmd->allcmd = cmd->allcmd->next;
		// ms_free_and_init_allcmd(&cmd->allcmd->previous);
		// cmd->allcmd = temp;
		// temp = temp->next;
		
	}
}

void	ms_free_doubletab(char **tab, int i)
{
	if (tab != NULL && *tab != NULL)
	{
		while (i > -1)
		{
			if (tab[i] != NULL)
			{
				free(tab[i]);
				tab[i] = NULL;
			}
			i--;
		}
		free(tab);
		tab = NULL;
	}
}

void	ms_free_and_init_dtab(char **tab)
{
	int i;

	i = 0;
	if (tab != NULL)
	{
		while (*tab[i])
		{
			if (tab[i] != NULL)
			{
				free(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	ms_free_and_init(char **str)
{
	free(*str);
	*str = NULL;
}

void	ms_free_and_init_token(t_token **token)
{
	free(*token);
	*token = NULL;
}

void	ms_free_and_init_allcmd(t_allcmd **allcmd)
{
	free(*allcmd);
	*allcmd = NULL;
}