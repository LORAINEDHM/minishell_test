#include "minishell.h"

void	error_msg(int error, char *str)
{
    ft_putstr("bash: ");
	if (error == CMD_NOT_FOUND)
    {
		ft_putstr(str);
		ft_putstr(": command not found");
    }

    if(error == EXPORT_UNVALID_IDENTIFIER 
        || UNSET_UNVALID_IDENTIFIER)
    {
        if (error == EXPORT_UNVALID_IDENTIFIER)
            ft_putstr("export: `");
        else
            ft_putstr("unset: `");
        ft_putstr(str);
		ft_putstr("': not a valid identifier");
    }
    ft_putstr("\n");
}