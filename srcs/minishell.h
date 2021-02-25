#ifndef MINISHELL_H
# define MINISHELL_H
# define S_Q 1
# define D_Q 2
# define S_CHEVRON 1
# define D_CHEVRON 2


# define INPUT 1
# define OUTPUT 2
# define DOUTPUT 4
# define CMD 8
# define ARG 16


/*
** -------------------------- External Headers ---------------------------------
*/

# include "../libs/libft/libft.h"
#include "../libs/GNL/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
//# include <linux/limits.h>
 # include <limits.h> // pour mac : vérifier s'il y a un #define PATH_MAX 4096 
# include <errno.h>
# include <string.h>
#include <dirent.h>  // opendir , closedir
# include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h> // NULL

typedef struct		s_env
{
	char *content;
	struct s_env *next;
	struct s_env *previous;
}					t_env;

typedef struct		s_token
{
	char *content;
	struct s_token *next;
	struct s_token *previous;
}					t_token;


typedef struct		s_allcmd
{
	int lastoutputtype;
	char *cmd;
	char *cmdpath;
	struct s_token *inputf; 
	struct s_token *inputl;
	struct s_token *outputf;
	struct s_token *outputl;
	struct s_token *doutputf;
	struct s_token *doutputl;
	struct s_token *argf;
	struct s_token *argl;
	struct s_allcmd *next;
	struct s_allcmd *previous;
}					t_allcmd;

typedef struct s_liste
{
	t_allcmd *first;
	t_allcmd *last;
}				t_liste;

typedef struct      s_cmd			
{
    int		i;
	int		j;
	int		k;
    int		fd;
	int		index;
	int		flag;
	int		error;
	int		g_envp_len;
	int		n_flag;
	int		token_len;
	int		pipe_nb;
	char	quoteflag;
	char	tokenflag;
	char	rdirflag;
	char	quotef;
	char	*line;
	char	*rest;
	char	*file_path;
	char	*token;
	char	*quotetab;
	char	*new_token;
	char	*cd;
	char 	*inputdata;
	char	*var_name;
	char	*content;
	char	**tab;
	DIR*	dir_ret;

	t_env	*env;
	t_env	*new_env;
	t_env	*env_first;
	t_allcmd *allcmd;
	t_allcmd *new_allcmd;
	t_liste *liste;
	// t_token *input;
	// t_token *output;
	// t_token *doutput;
	// t_token *arg;
	t_token *temp;
}				    t_cmd;

typedef struct      s_var			
{
	char	*line;
	char	*rest;
	int		name_length;
	int		start;
	int		end;
	int		value_length;
	int		line_length;
	char	*newline;
	char	*name;
	char	*value;
	int		flag_null;
	int		var_flag;
	int		quote_following_dollar;
}				    t_var;

typedef struct		s_pipe
{
	int		nb_str;
	int		index;
	int		split_flag;
}					t_pipe;


typedef struct      s_slash
{
	int		line_length;
	char	*newline;
	int		number;
}					t_slash;


typedef struct	s_path
{
	char	*path;
	struct s_path *next;
}				t_path;


typedef	enum	e_error
{
	CMD_NOT_FOUND,
	EXPORT_UNVALID_IDENTIFIER,
	UNSET_UNVALID_IDENTIFIER,
}				t_elem_error;

// typedef struct	s_envp
// {
// 	char *var;
// 	char *value;
// 	s_envp *next;
		
// }				t_envp;


/*
** -------------------------- Global variables ---------------------------------
*/

int		g_pid;
char    **g_envp;
// t_envp	*g_envpl;
//char	**g_temp;

/*
** --------------------------------- Defines -----------------------------------
*/

/*
** ------------------------- Enum Definitions ----------------------------------
*/

/*
** ------------------------- Structure Definitions -----------------------------
*/

/*
** -----------------------------------------------------------------------------
** ------------------------------- Sources -------------------------------------
** -----------------------------------------------------------------------------
*/

/*
** ---------------------------------- main.c -----------------------------------
*/

int    main(int ac, char *argv[], char *envp[]);


/*
** ---------------------------------- init.c -----------------------------------
*/

//void    ms_init_envp(t_cmd *cmd, int ac, char *argv[], char *envp[]);
void	ms_init_env_list(t_cmd *cmd, char *envp[]);
void	ms_init_cmd(t_cmd *cmd);

/*
** -------------------------------- display.c ----------------------------------
*/

void    ms_display_prompt_message(t_cmd *cmd);
int		ms_cmd_list(t_cmd *cmd);


/*
** --------------------------------- comma.c ----------------------------------
*/


int		ms_quoteflag(t_cmd *cmd, char c);
int		ms_check_semicolon(t_cmd *cmd);

/*
** --------------------------------- quotes.c ----------------------------------
*/

void	ms_check_quotes(t_cmd *cmd);


/*
** --------------------------------- parsing ------------------------------------
*/
// parsing.c
int    		ms_parsing(t_cmd *cmd);

// semicolon.c
void		ms_sep_semicolon(t_cmd *cmd);

// utils.c
void		ms_backslash_skip_next_c(char  *str, int *pos);
void		ms_quotes_skip(t_cmd *cmd, char *str, int *pos);

// pipe.c
char		**ms_pipe_split(t_cmd *cmd, t_pipe *pipe);

// autres.c
int     	ms_parsing_quotes(t_cmd *cmd);

void		ms_remove_quotes(t_cmd *cmd);
/*
** --------------------------------- path.c ----------------------------------
*/

void	ms_path(t_cmd *cmd, char *bash_cmd, t_allcmd *allcmd);
int		ms_test_path(t_cmd *cmd, char *path_dir, char *bash_cmd, t_allcmd *allcmd);
char    *ms_join_path(char *path_dir, char *bash_cmd);


/*
** --------------------------------- cmd.c ----------------------------------
*/



/*
** ------------------------------- dollar.c --------------------------------
*/

void	ms_dollar(t_cmd *cmd, t_var *var);
void	find_var_end(t_cmd *cmd, t_var *var);


/*
** ------------------------------- pipe.c --------------------------------
*/

char		*ms_strndup(const char *src, size_t n);

/*
** --------------------------------- slash.c ----------------------------------
*/


int		ms_backslash(t_cmd *cmd, t_slash *slash);
// int		ms_check_if_slash(t_cmd *cmd);
// int		ms_copy_newline_slash(t_cmd *cmd, t_slash *slash);


/*
** --------------------------------- token.c ----------------------------------
*/



/*
** ---------------------------------- utils.c ----------------------------------
*/

//char	*ms_get_env_var(char *envv);
char	*ms_get_env_var(t_cmd	*cmd, char *var);
int		ms_check_cmd_validity(t_cmd *cmd, char *envv);



/*
** ---------------------------------- error.c -----------------------------------
*/

void	error_msg(int error, char *str);

/*
** ---------------------------------- exit.c -----------------------------------
*/

void	ms_exit(void);

/*
** ---------------------------------- free.c -----------------------------------
*/

void	ms_free_char_array(char **arr);
void	ms_free_doubletab(char **tab, int i);
void	ms_free_all_lists(t_cmd *cmd);
void	ms_free_tokenlist(t_token **token);
void	ms_free_and_init(char **str);
void	ms_free_and_init_token(t_token **token);
void	ms_free_and_init_allcmd(t_allcmd **allcmd);
void	ms_free_and_init_dtab(char **tab);

/*
** ---------------------------------- pwd.c -----------------------------------
*/

void	ms_pwd(void);

/*
** ----------------------------- chained_list_utils.c -------------------------
*/

void ms_init_chained_list(t_allcmd *allcmd, t_liste *liste);
void		ms_init_memory();
t_allcmd	*ms_new_cmd(char *str);
void		ms_list_add_back(t_liste *liste, t_allcmd *allcmd);
char    *parse_cmd(char *str, int *i);
int		ft_isalpha_lowercase(int c);


/*
** ------------------------------------ token.c --------------------------------
*/


void    ms_token_to_struct(t_cmd *cmd);
int		ms_redirection_token(t_cmd *cmd);
int		ms_get_next_token(t_cmd *cmd);
// int		ms_identify_tokens(t_cmd *cmd);
int		ms_split_in_tokens(t_cmd *cmd);
// int		ms_copying_tokens(t_cmd *cmd);
// int		ms_remove_quotes(t_cmd *cmd);
void	ms_record_quotef(t_cmd *cmd);
int		ms_if_quotes(t_cmd *cmd);
int		ms_if_no_quotes(t_cmd *cmd);
// int		ms_remove_backslash(t_cmd *cmd);

/*
** --------------------------------- token_utils.c -----------------------------
*/

void	ms_malloc_lists(t_cmd *cmd);
void	ms_initialise_liste(t_cmd *cmd);
void	ms_malloc_new_lists(t_cmd *cmd);
void	ms_initialise_new_lists(t_cmd *cmd);
void	ms_addfront_token(t_cmd *cmd, t_token **all_token, t_token **last);

/*
** --------------------------------- builtins ----------------------------------
*/

int    	ms_builtins(t_cmd *cmd, t_allcmd *allcmd);
int		ms_which_builtin(t_cmd *cmd, t_allcmd *allcmd);
int		ms_echo(t_cmd *cmd, t_allcmd *allcmd);
void    ms_export(t_cmd *cmd, t_allcmd *allcmd);
void    ms_unset(t_cmd *cmd, t_allcmd *allcmd);
int     ms_check_validy(char *content, int *index);
void    ms_cd(t_cmd *cmd, t_allcmd *allcmd);
void    ms_env(t_cmd *cmd);

/*
** ---------------------------------- seek_cmd.c ------------------------------
*/

/*
** ---------------------------------- fork.c ----------------------------------
*/

int     ms_fork(t_allcmd *allcmd, t_cmd *cmd);

/*
** ------------------------------- execute.c ----------------------------------
*/

int			ms_execve(t_cmd *cmd, t_allcmd *allcmd);

/*
** ------------------------------- redirections.c ------------------------------
*/

int			ms_redirections(t_cmd *cmd, t_allcmd *allcmd);
void    	ms_handle_o_s_redirections(t_cmd *cmd, t_allcmd *allcmd);
void    	ms_handle_o_d_redirections(t_cmd *cmd, t_allcmd *allcmd);
void    	ms_handle_i_redirections(t_cmd *cmd, t_allcmd *allcmd);
char		*ms_return_path(char *cd, char *filename);



#endif
