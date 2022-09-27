#include "minishell.h"
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("type: %d, value: %s\n", tokens->e_type, tokens->value);
		tokens = tokens->next;
	}
}
void	print_lexer(t_lex *lex)
{
	printf("char : %c\n", lex->c);
	printf("indice : %i\n", lex->i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_strndup(char *str, int i)
{
	char	*dup;
	int		j;

	j = 0;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	while (j < i)
	{
		dup[j] = str[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	advance_lex(t_lex *lex)
{
	lex->i++;
	lex->c = lex->cmd[lex->i];
}
void	token_squote(t_lex *lex, t_token *tokens)
{
	tokens->e_type = SQUOTE;
	tokens->value = ft_strdup("");
	advance_lex(lex);
	while (lex->c != '\'')
	{
		tokens->value = ft_strjoin(tokens->value, ft_strndup(&lex->c, 1));
		advance_lex(lex);
	}
	advance_lex(lex);
}

void	token_dquote(t_lex *lex, t_token *tokens)
{
	tokens->e_type = DQUOTE;
	tokens->value = ft_strdup("");
	advance_lex(lex);
	while (lex->c != '"')
	{
		tokens->value = ft_strjoin(tokens->value, ft_strndup(&lex->c, 1));
		advance_lex(lex);
	}
	advance_lex(lex);
}

void	create_tokens(t_lex *lex, t_token *tokens)
{
	while(lex->c)
	{
		if(lex->c == 32 || lex-> c == 9)
			advance_lex(lex);
		else if (lex->c == '\'')
			token_squote(lex, tokens);
		else if (lex->c == '\"')
			token_dquote(lex, tokens);
		// else if (lex->c == '|')
		// 	token_pipe(lex, tokens);
		// else if (lex->c == '>')
		// 	token_great(lex, tokens);
		// else if (lex->c == '<')
		// 	token_less(lex, tokens);
		// else if (lex->c == '$')
		// 	token_dollar(lex, tokens);
		// else
		// 	token_word(lex);
	}
}

void	*init_create_tokens(t_token *tokens, t_parse *parse, char *line)
{
	t_lex	*lex;
    parse = malloc(sizeof(t_parse));
	lex = malloc(sizeof(t_lex));
	tokens = malloc(sizeof(t_token));
    if (!parse || !lex)
        return (NULL);
    parse->ags = NULL;
    parse->cmd = NULL;
    parse->next = NULL;
	lex->c = line[0];
	lex->cmd = line;
	lex->i = 0;
	create_tokens(lex, tokens);
	return (NULL);
}

int	main(int ac, char *av[], char **env)
{
	t_parse	*parse;
	t_token	*tokens;
    char    *line;

	tokens = NULL;
	(void)ac;
	(void)av;
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			exit(0);
		init_create_tokens(tokens, parse, line);
		// create_commands(tokens, &commands);
	}
}
