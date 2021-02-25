#include "minishell.h"

void	ms_exit(void)
{
	ft_putstr(strerror(ENOMEM));
    if (g_envp)
	    ms_free_char_array(g_envp);
	write(1, "\n", 1);
	exit(0);
}