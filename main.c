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
		// else if (lex->c == '\'')
		// 	token_squote(lex, tokens);
		// else if (lex->c == '\"')
		// 	token_dquote(lex, tokens);
		else if (lex->c == '|')
			token_pipe(lex, tokens);
		else if (lex->c == '>')
			token_great(lex, tokens);
		else if (lex->c == '<')
			token_less(lex, tokens);
		// else if (lex->c == '$')
		// 	token_dollar(lex, tokens);
		else
			token_word(lex, tokens);
	}
	return(tokens);
}

t_token	*init_create_tokens(t_token *tokens, t_parse *parse, char *line)
{
	t_lex	*lex;
    parse = malloc(sizeof(t_parse));
	lex = malloc(sizeof(t_lex));
	tokens = init_token(NULL, 0);
    if (!parse || !lex || !tokens)
        return (NULL);
    parse->ags = NULL;
    parse->cmd = NULL;
    parse->next = NULL;
	lex->c = line[0];
	lex->cmd = line;
	lex->i = 0;
	tokens = create_tokens(lex, tokens);
	return (tokens);
}

int	main(int ac, char *av[], char **env)
{
	t_parse	*parse;
	t_token	*tokens;
    char    *line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("MISSI-1.0$ ");
		if (!line)
			exit(0);
		tokens = init_create_tokens(tokens, parse, line);
		print_tokens(tokens);
	}
}
