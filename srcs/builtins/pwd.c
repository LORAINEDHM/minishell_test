#include "../minishell.h"

void	ms_pwd(void)
{
    char	buff[PATH_MAX + 1];

    if (!(getcwd(buff, PATH_MAX + 1)))
        ms_exit();
    ft_putstr(buff);
    write(1, "\n", 1);
}
