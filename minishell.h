#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
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

typedef struct s_token
{
	char			*val;
	int				flag;
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

typedef struct s_parse
{
	char			*cmd;
	char			**ags;
	struct s_parse	*next;
}		t_parse;

#endif
