#include "../minishell.h"



static void	ms_init(t_cmd *cmd, t_var *var)
{
	var->var_flag = 0;
	var->value_length = 0;
	var->name_length = 0;
	var->start = 0;
	var->end = 0;
	cmd->i = 0;
	cmd->quoteflag = 0;
	var->name = NULL;
	var->value = NULL;
    var->newline = NULL;
	return;
}

static void	ms_find_var_name_end(t_cmd *cmd, t_var *var)
{
	int i;

	i = 0;
	var->start = cmd->i;
	var->var_flag = 1;  // = var found
	while(cmd->line[cmd->i] != '\0'
		&& ((ft_isalnum(cmd->line[cmd->i]) == 1)
		|| (cmd->line[cmd->i] == '_')))
	{
		if (var->name_length == 0 && (ft_isdigit(cmd->line[cmd->i]) == 1)) // a variable can't start by a digit
		{
			var->start += 1;
			var->name_length = 1;
			i = 1;
			break; 
		}
		var->name_length++;
		cmd->i++;
	}
	if (var->name_length == 0 && (cmd->line[cmd->i] == 34 || cmd->line[cmd->i] == 39))
	{
		if (cmd->quoteflag == 0)
		{
			var->start += 1;
			i = 1;
		}
		// else
		// {
		// 	var->start  += 1;
		// 	var->name_length = 1;
		// 	i = 0;
		// }
	}
	var->end = var->start + var->name_length - 1 - i;
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

static void		ms_check_var_exist(t_cmd *cmd, t_var *var)
{
	if (!(var->value = ms_get_env_var(cmd, var->name)))
	{
		var->start -= 1;
		(printf("VAR DOES NOT EXIST\n"));  // VERIFIER QUEL MESSAGE D ERREUR METTRE
	}
	else
	{
		var->value_length = ft_strlen(var->value);
	}
}

static void		ms_copy_var_name(t_cmd *cmd, t_var *var)
{
	int i;
	int j;

	i = var->start;
	j = 0;
	if (!(var->name = malloc(sizeof(char) * (var->name_length + 1))))
		exit(0);
	while (j < var->name_length)
	{
		var->name[j] = cmd->line[i];
		j++;
		i++;
	}
	var->name[j] = '\0';
	//printf("var_name = %s\n", var->name);
	ms_check_var_exist(cmd, var);
	ms_free_and_init(&var->name);
}

static int		ms_have_newline_length(t_var *var)
{
	int i;

	i = 0;
	if (var->var_flag == 0)
		i = var->line_length - var->name_length + var->value_length;
	else
		i = var->line_length - var->name_length + var->value_length - 1;  // because we don't print $ char
	//printf("newline lenght = %d\n", i);
	return (i);
}

static void		ms_copy_newline_dollar(t_cmd *cmd, t_var *var)
{
	int newline_length;
	int i;
	int j;

	i = 0;
	j = 0;
	newline_length = ms_have_newline_length(var);
	if (!(var->newline = (malloc(sizeof(char) * (newline_length + 1)))))
		exit(0);
	cmd->i = 0;
	while (cmd->line[cmd->i] != '\0')
	{

		if (var->var_flag == 1 && i == var->start - 1)
		{
			while (var->value != NULL && var->value[j] != '\0')
				var->newline[i++] =  var->value[j++];
			if (cmd->line[var->end + 1] != '\0')
			{
				cmd->i = var->end + 1;
			}
			else
				break; // i = 0
		}
		var->newline[i++] = cmd->line[cmd->i++];
	}
	var->newline[i] = '\0';
}


static void		ms_check_and_record_variable(t_cmd *cmd, t_var *var)
{
    while (cmd->line[cmd->i] != '\0')
    {
		ms_check_backslash(cmd);
        if (cmd->line[cmd->i] == '$' && !(S_Q & cmd->quoteflag)
			&& cmd->line[cmd->i + 1] != '\0' && cmd->line[cmd->i + 1] != ' ')
        {
			cmd->i++;
			if (cmd->quoteflag != 0 && (var->name_length == 0 
				&& (cmd->line[cmd->i] == 34 || cmd->line[cmd->i] == 39)))
				break;
			ms_find_var_name_end(cmd, var);
			ms_copy_var_name(cmd, var);
			ms_copy_newline_dollar(cmd, var);
			ms_free_and_init(&cmd->line);
			cmd->line = ft_strdup(var->newline);
			ms_free_and_init(&var->newline);
			break;
		}
		cmd->i++;
    }
}

void		ms_dollar(t_cmd *cmd, t_var *var)
{

	while(cmd->line)
	{
		ms_init(cmd, var);
		var->line_length = ft_strlen(cmd->line);
   		ms_check_and_record_variable(cmd, var);
		if (var->var_flag == 0)
			break;
	}
}
