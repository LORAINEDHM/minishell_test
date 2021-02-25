#include "../minishell.h"

// void		ms_backslash_skip_next_c(char  *str, int *pos) // return 0 save 1 unsave
// {
//     while (str[*pos] == 92)
//         *pos += 2;
// }

// void		ms_quotes_skip(t_cmd *cmd, char *str, int *pos) // return 0 save 1 unsave
// {
//     ms_quoteflag(cmd, str[*pos]);
//     while(S_Q & cmd->quoteflag || D_Q & cmd->quoteflag)
//     {
//         (*pos)++;
//         ms_quoteflag(cmd, str[*pos]);
//     }
// }