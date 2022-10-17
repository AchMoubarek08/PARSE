
#include "minishell.h"

int	kayn_token(char *str)
{
	char	*tokens;
	int		i;
	int		j;

	tokens = "$><|'\"";
	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (tokens[j])
		{
			if (str[i] == tokens[j] || str[i] == ' ')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

void	print_tokens(t_token *tokens)
{
	char *type;
	while (tokens)
	{
		if(tokens->e_type == 0)
			type = strdup("WORD");
		else if(tokens->e_type == 4)
			type = strdup("PIPE");
		else if(tokens->e_type == 5)
			type = strdup("GnG ");
		else if(tokens->e_type == 7)
			type = strdup("G   ");
		else if(tokens->e_type == 6)
			type = strdup("LnL ");
		else if(tokens->e_type == 8)
			type = strdup("L   ");
		else if(tokens->e_type == 10)
			type = strdup("END ");
		printf("type: %s   value: %s\n", type, tokens->value);
		tokens = tokens->next;
	}
}
void	print_lexer(t_lex *lex)
{
	printf("char : %c\n", lex->c);
	printf("indice : %i\n", lex->i);
}

t_token	*init_token(char *val, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = val;
	token->next = NULL;
	token->e_type = type;
	return (token);
}

void	advance_lex(t_lex *lex)
{
	lex->i++;
	lex->c = lex->cmd[lex->i];
}
t_token	*create_tokens(t_lex *lex, t_token *tokens)
{
	while(lex->c)
	{
		if(lex->c == 32 || lex-> c == 9)
			advance_lex(lex);
		else if (lex->c == '|')
			token_pipe(lex, tokens);
		else if (lex->c == '>')
			token_great(lex, tokens);
		else if (lex->c == '<')
			token_less(lex, tokens);
		else
			token_word(lex, tokens);
	}
	end_token(tokens);
	return(tokens);
}

t_token	*init_create_tokens(t_token *tokens, char *line)
{
	t_lex	*lex;
	lex = malloc(sizeof(t_lex));
	tokens = init_token(NULL, 0);
    if (!lex || !tokens)
        return (NULL);
	lex->c = line[0];
	lex->cmd = line;
	lex->i = 0;
	tokens = create_tokens(lex, tokens);
	return (tokens);
}

t_parse	*init_cmd(void)
{
	t_parse	*command;

	command = (t_parse *)malloc(sizeof(t_parse));
	if (!command)
		return (NULL);
	command->cmd = NULL;
	command->argv = (char **)realloc_array(NULL, ft_strdup(""));
	command->redir = NULL;
	command->next = NULL;
	return (command);
}
t_parse	*add_command_back(t_parse *lst, t_parse *new)
{
	t_parse	*tmp;

	tmp = lst;
	if (!lst)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}
void	print_parse(t_parse *parse)
{
	int i;
	while (parse)
	{
		i = 0;
		if (parse->cmd)
			printf("cmd: %s\n", parse->cmd);
		while(parse->argv[i])
		{
			printf("argv: %s\n", parse->argv[i]);
			i++;
		}
		if(parse->redir && parse->redir->file)
		{
			while(parse->redir)
			{
				printf("redir type : %d\n", parse->redir->e_type);
				printf("redir: %s\n", parse->redir->file);
				printf("redir fdin: %d\n", parse->redir->fdin);
				printf("redir fdout: %d\n", parse->redir->fdout);
				parse->redir = parse->redir->next;
			}
		}
		parse = parse->next;
	}
}
void	*f_malloc(size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (!tmp)
		return (NULL);
	g_vars.alloc[g_vars.index] = tmp;
	g_vars.index++;
	return (tmp);
}

static int	countword(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

char	*allocwords(char const *s, char c, int i)
{
	int		j;
	char	*str;

	j = i;
	while (s[j] != c && s[j])
	{
		j++;
	}
	str = f_malloc(sizeof(char) * j + 1);
	if (str == NULL)
		return (0);
	j = 0;
	while (s[i] && s[i] != c)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	if (!s)
		return (0);
	str = f_malloc(sizeof(char *) * (countword(s, c) + 1));
	if (str == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
		{
			str[j] = allocwords(s, c, i);
			j++;
		}
		i++;
	}
	str[j] = NULL;
	return (str);
}

t_env	*lst_new(char *key, char sep, char *val)
{
	t_env	*new;

	new = f_malloc(sizeof(t_env));
	new->key = key;
	new->val = val;
	new->sep = sep;
	new->next = NULL;
	return (new);
}

void	lst_add_backenv(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = *lst;
	if (!new)
		return ;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
char	*my_getenv(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = (env);
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}
void	init_env(char **env)
{
	char	*key;
	char	*val;
	int		i;
	char	**tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		key = tmp[0];
		val = tmp[1];
		lst_add_backenv(&g_vars.my_env, lst_new(key, '=',
				val));
		i++;
	}
	lst_add_backenv(&g_vars.my_env, lst_new("0", '=', "minishell"));
}

int	main(int ac, char *av[], char **env)
{
	t_parse	*parse;
	t_token	*tokens;
    char    *line;

	(void)ac;
	(void)av;
	init_env(env);
	while (1)
	{
		line = readline("MISSI-1.0$ ");
		if (!line)
			exit(0);
		parse = init_cmd();
		tokens = init_create_tokens(tokens, line);
		tokens = parsing(tokens, &parse);
		// print_tokens(tokens);
		fill_tparse(tokens, &parse);
		print_parse(parse);
		add_history(line);
	}
}
