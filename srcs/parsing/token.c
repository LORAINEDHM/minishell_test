#include "../minishell.h"

static void	ms_init(t_cmd *cmd)
{
	cmd->flag = 0;
	cmd->i = 0;
	cmd->index = 0;
	cmd->token = NULL;
}

static void		save_token_into_list(t_cmd *cmd)
{
	if (cmd->line[cmd->i] == '<' || cmd->line[cmd->i] == '>')
		{
			ms_redirection_token(cmd);
			cmd->i++;
			ms_get_next_token(cmd);
			ms_token_to_struct(cmd);
		}
	else
		{
			if (cmd->flag == 0)  // means cmd word not found yet
			{
				cmd->tokenflag |= CMD;
				ms_get_next_token(cmd);
				cmd->flag = 1;
			}
			else  // means cmd word already found, so words = args
			{
				cmd->tokenflag |= ARG;
				ms_get_next_token(cmd);
			}
			ms_token_to_struct(cmd);
		}
}

static void		ms_identify_tokens(t_cmd *cmd)
{
	ms_init(cmd);
	
	while(cmd->line[cmd->i] != '\0')
	{
		cmd->tokenflag = 0;
		cmd->token = NULL;
		while (cmd->line[cmd->i] == ' ')
			cmd->i++;
		save_token_into_list(cmd);
		
		if (cmd->line[cmd->i] == '\0')
			break;
		cmd->i++;
	}
}

static t_liste *ms_new_t_liste()
{
	t_liste *liste;

	if (!(liste = malloc(sizeof(t_liste))))
		exit(0);
	liste->first = NULL;
	liste->last = NULL;
	return (liste);
}

int		ms_split_in_tokens(t_cmd *cmd)
{
    int j;
	int first_flag;
    j = 0;
	// printf("hello 1 \n");
	cmd->liste = ms_new_t_liste();
	// printf("hello 2 \n");
	// malloc(sizeof(t_liste));
	// ms_initialise_liste(cmd);

	first_flag = 0; // will be 1 when allcmd list has at least 1 element
    while (cmd->tab && cmd->tab[j] != NULL) 
	{
		// printf("hello 1 \n");
		cmd->new_allcmd = malloc(sizeof(t_allcmd));
		ms_initialise_new_lists(cmd);
		// printf("hello 2 \n");
		ms_free_and_init(&cmd->line); 
		cmd->line = ft_strdup(cmd->tab[j]);
		if (first_flag == 1)  // already 1 allcmd list filled
		{
			cmd->new_allcmd->next = cmd->allcmd;  
			cmd->new_allcmd->next->previous = cmd->new_allcmd;
			cmd->allcmd = cmd->new_allcmd;
		}
		else  // 1st allcmd list to fill
		{
			cmd->allcmd = cmd->new_allcmd;
			printf("hey\n");
			// cmd->allcmd->next = NULL;
			// cmd->allcmd->previous = NULL;
			first_flag = 1;
		}
		ms_identify_tokens(cmd);
		printf("hey2\n");
		cmd->liste->first = cmd->allcmd;
		//printf("cmd->liste->first = %p\n", cmd->liste->first);
		if (cmd->allcmd->next == NULL)
		{
			cmd->liste->last = cmd->allcmd;
		}
		cmd->allcmd->previous = NULL;
		j++;
	}
	cmd->temp = NULL;

printf ("\n\n");

//	printf("cmd->liste->first->cmd0 = %p\n", cmd->liste->first);
	cmd->allcmd = cmd->liste->first;
//	printf("cmd->liste->first->cmd1 = %p\n", cmd->liste->first);
	while (cmd->allcmd)
	{
		printf ("while\n");
		printf("allcmd->cmd = %s\n", cmd->allcmd->cmd);
		cmd->temp = cmd->allcmd->inputf;
		while (cmd->temp)
		{
			printf("input while = %s\n", cmd->temp->content);
			cmd->temp = cmd->temp->next;
		}
		cmd->temp = cmd->allcmd->outputf;
		while (cmd->temp)
		{
			printf("output while = %s\n", cmd->temp->content);
			cmd->temp = cmd->temp->next;
		}
		cmd->temp = cmd->allcmd->doutputf;
		while (cmd->temp)
		{
			printf("doutput while = %s\n", cmd->temp->content);
			cmd->temp = cmd->temp->next;
		}
		cmd->temp = cmd->allcmd->argf;
		while (cmd->temp)
		{
			printf("arg while = %s\n", cmd->temp->content);
			cmd->temp = cmd->temp->next;
		}
		cmd->allcmd = cmd->allcmd->next;
		printf("------\n");

	//	printf("cmd->liste->first->cmd2 = %s\n", cmd->liste->first->cmd);
	}





	// REMETTRE A L ENDROIT

	printf("\n\nREVERSE\n\n");

	cmd->allcmd = cmd->liste->last;
	while (cmd->allcmd)
	{
		printf ("while\n");
		printf("allcmd->cmd = %s\n", cmd->allcmd->cmd);
		cmd->temp = cmd->allcmd->inputl;
		while (cmd->temp)
		{
			printf("input while = %s\n", cmd->temp->content);
			cmd->temp = cmd->temp->previous;
		}
		cmd->temp = cmd->allcmd->outputl;
		while (cmd->temp)
		{
			printf("output while = %s\n", cmd->temp->content);
			cmd->temp = cmd->temp->previous;
		}
		cmd->temp = cmd->allcmd->doutputl;
		while (cmd->temp)
		{
			printf("doutput while = %s\n", cmd->temp->content);
			cmd->temp = cmd->temp->previous;
		}
		cmd->temp = cmd->allcmd->argl;
		while (cmd->temp)
		{
			printf("arg while = %s\n", cmd->temp->content);
			cmd->temp = cmd->temp->previous;
		}
		cmd->allcmd = cmd->allcmd->previous;
		printf("------\n");
	}

	cmd->allcmd = NULL;
	cmd->temp = NULL;



// cmd->allcmd = cmd->liste->first;
// //	printf("cmd->liste->first->cmd1 = %p\n", cmd->liste->first);
// 	while (cmd->allcmd)
// 	{
// 		printf ("while\n");
// 		printf("allcmd->cmd = %s\n", cmd->allcmd->cmd);
// 		cmd->temp = cmd->allcmd->inputf;
// 		while (cmd->temp)
// 		{
// 			printf("input while = %s\n", cmd->temp->content);
// 			cmd->temp = cmd->temp->next;
// 		}
// 		cmd->temp = cmd->allcmd->outputf;
// 		while (cmd->temp)
// 		{
// 			printf("output while = %s\n", cmd->temp->content);
// 			cmd->temp = cmd->temp->next;
// 		}
// 		cmd->temp = cmd->allcmd->doutputf;
// 		while (cmd->temp)
// 		{
// 			printf("doutput while = %s\n", cmd->temp->content);
// 			cmd->temp = cmd->temp->next;
// 		}
// 		cmd->temp = cmd->allcmd->argf;
// 		while (cmd->temp)
// 		{
// 			printf("arg while = %s\n", cmd->temp->content);
// 			cmd->temp = cmd->temp->next;
// 		}
// 		cmd->allcmd = cmd->allcmd->next;
// 		printf("------\n");

// 	//	printf("cmd->liste->first->cmd2 = %s\n", cmd->liste->first->cmd);
// 	}

	//printf("cmd->liste->first->cmd3 = %s\n", cmd->liste->first->cmd);

// 	 printf("TEST\n");
// 	cmd->allcmd = cmd->liste->first;
// //	cmd->temp = cmd->allcmd->argl;
// 	printf("cmd->allcmd->argf->content = %s\n", cmd->allcmd->argf->content);
	//cmd->temp = cmd->allcmd->argl;
	// //printf("arg->content = %s\n", cmd->allcmd->argl->content);
	// cmd->allcmd = cmd->liste->first;
	// printf("arg->content = %s\n", cmd->allcmd->argf->content);


	// cmd->liste->first = cmd->liste->first->next;

	// while (cmd->liste->first)
	// {
	// 	printf ("while\n");
	// 	printf("allcmd->cmd = %s\n", cmd->liste->first->cmd);
	// 	while (cmd->liste->first->input)
	// 	{
	// 		printf("input while = %s\n", cmd->liste->first->input->content);
	// 		printf("len = %zu\n", ft_strlen(cmd->liste->first->input->content));
	// 		cmd->liste->first->input = cmd->liste->first->input->next;
	// 	}
	// 	while (cmd->liste->first->output)
	// 	{
	// 		printf("output while = %s\n", cmd->liste->first->output->content);
	// 		printf("len = %zu\n", ft_strlen(cmd->liste->first->output->content));
	// 		cmd->liste->first->output = cmd->liste->first->output->next;
	// 	}
	// 	while (cmd->liste->first->doutput)
	// 	{
	// 		printf("doutput while = %s\n", cmd->liste->first->doutput->content);
	// 		printf("len = %zu\n", ft_strlen(cmd->liste->first->doutput->content));
	// 		cmd->liste->first->doutput = cmd->liste->first->doutput->next;
	// 	}
	// 	while (cmd->liste->first->arg)
	// 	{
	// 		printf("arg while = %s\n", cmd->liste->first->arg->content);
	// 		printf("len = %zu\n", ft_strlen(cmd->liste->first->arg->content));
	// 		cmd->liste->first->arg = cmd->liste->first->arg->next;
	// 	}
	// 	//liste->first = liste->first->next;
	// 	cmd->liste->first = cmd->liste->first->next;
	// 	printf("------\n");

	

	// }
    return (0);
}
