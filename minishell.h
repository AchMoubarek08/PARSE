#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <strings.h>
# include <stdlib.h>
# include <ctype.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_lex
{
	char	*cmd;
	int		i;
	char	c;
}	t_lex;

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
	enum
	{
		WORD,
		DQUOTE,
		SQUOTE,
		BACKSLASH,
		PIPE,
		GREATANDGREAT,
		LESSANDLESS,
		GREAT,
		LESS,
		DOLLAR,
		END,
	} e_type;
}		t_token;

typedef struct s_redir
{
	char			*file;
	int				e_type;
	int				fdout;
	int				fdin;
	struct s_redir	*next;

}		t_redir;

typedef struct s_parse
{
	char			*cmd;
	char			**argv;
	t_redir			*redir;
	struct s_parse	*next;
}		t_parse;

// get_next_line
void	nadi(char **stock, char **ligne);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
size_t	ft_strlen_gnl(const char *str);
char	*ft_strdup_gnl(const char *s);
int		ft_int_strchr_gnl(const char *s, int c);
char	*ft_free(char **lost);
char	*get_next_line(int fd);


void	advance_lex(t_lex *lex);
t_token	*lst_add_back(t_token *lst, t_token *new);
int		ft_isdigit(int c);
int		ft_is_space(char *str);
char	*ft_strdup(char *str);
char	*ft_strndup(char *str, int i);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
t_token	*init_create_tokens(t_token *tokens, char *line);
void	print_lexer(t_lex *lex);
t_token	*lst_add_back(t_token *lst, t_token *new);
t_token	*init_token(char *val, int type);
t_token	*create_tokens(t_lex *lex, t_token *tokens);
void	print_tokens(t_token *tokens);
void	token_dollar(t_lex *lex, t_token *tokens);
void	token_great(t_lex *lex, t_token *tokens);
void	token_less(t_lex *lex, t_token *tokens);
void	token_pipe(t_lex *lex, t_token *tokens);
void	token_dquote(t_lex *lex, t_token *tokens);
void	token_squote(t_lex *lex, t_token *tokens);
void	token_word(t_lex *lex, t_token *tokens);
void	end_token(t_token *tokens);


t_token	*parsing(t_token *tokens, t_parse **parse);
t_parse	*init_cmd(void);
void	*realloc_array(char **arg, char *str);
void	fill_tparse(t_token *tokens, t_parse **parse);
t_parse	*add_command_back(t_parse *lst, t_parse *new);
void	print_parse(t_parse *parse);

#endif
