#include "minishell.h"

void    ms_display_prompt_message(t_cmd *cmd)
{
    char	buff[PATH_MAX + 1];
    char    *prompt;
    size_t  length;

    prompt = NULL;
	if (!(getcwd(buff, PATH_MAX + 1)))
        ms_exit();  
   // printf("env_first->content = %s\n", cmd->env_first->content);
    length = ft_strlen(ms_get_env_var(cmd, "HOME"));
  //  printf("env_first->content = %s\n", cmd->env_first->content);
    if (!(prompt = ft_strjoin("~", &buff[length])))
        ms_exit();
    ft_putstr("\033[1m\033[33msim\033[31m♥\033[32mlolo\033[0m:\033[0;34m\033[1m");
    ft_putstr(prompt);
    ft_putstr("\033[0m$");
    free(prompt);
    // free(cwd); // qu'on m'explique
}
