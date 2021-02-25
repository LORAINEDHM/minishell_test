#include "minishell.h"

int ms_nb_elem_allcmd(t_allcmd *allcmd)
{
    int i;
    t_allcmd temp;

    temp = allcmd;
    i = 1;
    while (temp->next)
    {
        i++;
        temp = temp->next;
    }
    return (i);
}

ms_reverse_allcmd(t_allcmd *allcmd)
{
    int i;
    int nb;
    t_allcmd allcmd;

    i = 0;
    nb = ms_nb_elem_allcmd(allcmd);
    while (i > nb/2)
    {
        allcmd = ms_return_spec_allcmd(allcmd, elem);
    }
}

t_allcmd    *ms_return_spec_allcmd(allcmd, elem)
{
    int i;
    t_allcmd temp;

    i = 1;
    temp = allcmd;
    while (i != elem)
    {
        temp = temp->next;
        i++;
    }
    return (temp);
}

void    ms_previous_allcmd(t_allcmd *first)
{
    t_allcmd temp;

    temp = first;
    while (temp->next)
    {
        temp->next->previous = temp;
        temp = temp->next;
    }

}

typedef struct		s_allcmd
{
    char *cmd;
	int pipe;
	struct s_arguments *arguments;
	struct s_inputs *input; 
	struct s_outputs *output; 
	struct s_doutputs *doutput;
	struct s_allcmd *next;
	struct s_allcmd *previous;
	int	error;
}					t_allcmd;
